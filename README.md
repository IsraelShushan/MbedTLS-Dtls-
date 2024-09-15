# DTLS Application

## Features and Updates

This application has been updated with new features to enhance its DTLS protocol support and user configuration options.

### Main Window

The following updates were made to the main window:

- **Cipher Suites:** A combobox has been added to allow users to choose the desired cipher suite.
  
  ![Cipher Suite](./images/cipher_suite.png) <!-- Image placeholder for cipher suite -->
  
- **Common Name of the Server:** Clients can now provide the server's common name for verification.
  
  ![Common Name](./images/common_name.png) <!-- Image placeholder for common name -->
  
- **Persistent Checkbox:** A new option has been added to save the session key after the first handshake for session persistence.

  ![Persistent Checkbox](./images/persistent_checkbox.png) <!-- Image placeholder for persistent checkbox -->
  
- **Add Server Verification (Optional):** An option for two-sided verification has been added.

  ![Server Verification](./images/server_verification.png) <!-- Image placeholder for server verification -->
  
- **DTLS Server Port:** A button to configure the DTLS server port is now available.

  ![DTLS Server Port](./images/dtls_server_port.png) <!-- Image placeholder for DTLS server port -->

### Settings Window - Network Tab

Updates to the Network Tab include:

- **Send Simple Acknowledge:** A checkbox to enable simple acknowledgment sending.
  
  ![Send Acknowledge](./images/send_acknowledge.png) <!-- Image placeholder for send acknowledge -->
  
- **Enable DTLS Server:** Users can now enable the DTLS server and choose a specific port.

  ![Enable DTLS Server](./images/enable_dtls.png) <!-- Image placeholder for enable DTLS -->
  
- **Certificates and Keys:** Certificates and keys can now be loaded in the same way as SSL certificates and keys.

  ![Certificates and Keys](./images/certificates_and_keys.png) <!-- Image placeholder for certificates and keys -->

### Settings Window - Smart Responses Tab

- **Smart Responses:** Smart responses now function using the DTLS protocol for enhanced communication capabilities.

  ![Smart Responses](./images/smart_responses.png) <!-- Image placeholder for smart responses -->

### Wireshark Integration

The application provides examples of both regular connection creation and persistent connections using Wireshark for monitoring.

- **Regular Connection Example:**

  ![Wireshark Regular Connection](./images/wireshark_regular_connection.png) <!-- Image placeholder for Wireshark regular connection -->
  
- **Persistent Connection Example:**

  ![Wireshark Persistent Connection](./images/wireshark_persistent_connection.png) <!-- Image placeholder for Wireshark persistent connection -->

---

Make sure to replace the placeholder image paths (e.g., `./images/image_name.png`) with actual image URLs or file paths once the images are uploaded to the appropriate location in your project.

