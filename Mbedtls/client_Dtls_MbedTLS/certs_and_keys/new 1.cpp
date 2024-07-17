#include "mbedtls/net_sockets.h"
#include "mbedtls/ssl.h"
#include "mbedtls/error.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT "4433"
#define MAX_DATA_SIZE 1024

int main() {
    int ret;
    mbedtls_net_context listen_fd, client_fd;
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_ssl_context ssl;
    mbedtls_ssl_config conf;
    unsigned char buf[MAX_DATA_SIZE];
    const char *pers = "dtls_server";

    mbedtls_net_init(&listen_fd);
    mbedtls_net_init(&client_fd);
    mbedtls_ssl_init(&ssl);
    mbedtls_ssl_config_init(&conf);
    mbedtls_ctr_drbg_init(&ctr_drbg);
    mbedtls_entropy_init(&entropy);

    ret = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy,
                                 (const unsigned char *)pers, strlen(pers));
    if (ret != 0) {
        printf("mbedtls_ctr_drbg_seed failed\n");
        goto exit;
    }

    ret = mbedtls_ssl_config_defaults(&conf,
                                      MBEDTLS_SSL_IS_SERVER,
                                      MBEDTLS_SSL_TRANSPORT_DATAGRAM,
                                      MBEDTLS_SSL_PRESET_DEFAULT);
    if (ret != 0) {
        printf("mbedtls_ssl_config_defaults failed\n");
        goto exit;
    }

    mbedtls_ssl_conf_rng(&conf, mbedtls_ctr_drbg_random, &ctr_drbg);

    ret = mbedtls_ssl_setup(&ssl, &conf);
    if (ret != 0) {
        printf("mbedtls_ssl_setup failed\n");
        goto exit;
    }

    ret = mbedtls_net_bind(&listen_fd, NULL, SERVER_PORT, MBEDTLS_NET_PROTO_UDP);
    if (ret != 0) {
        printf("mbedtls_net_bind failed\n");
        goto exit;
    }

    while (1) {
        printf("Waiting for a new connection...\n");

        ret = mbedtls_net_accept(&listen_fd, &client_fd, NULL, 0, NULL);
        if (ret != 0) {
            printf("mbedtls_net_accept failed\n");
            continue;
        }

        mbedtls_ssl_set_bio(&ssl, &client_fd,
                            mbedtls_net_send, mbedtls_net_recv, NULL);

        printf("Handshaking...\n");
        ret = mbedtls_ssl_handshake(&ssl);
        if (ret != 0) {
            printf("mbedtls_ssl_handshake failed\n");
            mbedtls_net_free(&client_fd);
            continue;
        }

        printf("Handshake complete. Echoing back messages.\n");

        while ((ret = mbedtls_ssl_read(&ssl, buf, sizeof(buf))) > 0) {
            ret = mbedtls_ssl_write(&ssl, buf, ret);
            if (ret <= 0) {
                printf("mbedtls_ssl_write failed\n");
                break;
            }
        }

        mbedtls_ssl_close_notify(&ssl);
        mbedtls_net_free(&client_fd);
    }

exit:
    mbedtls_ssl_free(&ssl);
    mbedtls_ssl_config_free(&conf);
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);
    mbedtls_net_free(&listen_fd);
    mbedtls_net_free(&client_fd);

    return ret;
}
