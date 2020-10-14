Revision History

07/15/2018  NX Secure generic code version 5.11SP1. This release includes the
            following major features:

        Files are modified to update scratch buffers to support the new
          default 4096-bit RSA key size:
            nx_secure_tls_process_certificate_verify.c
            nx_secure_tls_process_client_key_exchange.c
            nx_secure_tls_send_certificate_verify.c
            nx_secure_tls_send_client_key_exchange.c
            

        Files are modified to fix issue with processing CertificateVerify
          messages in a TLS Server with Client X.509 Certificate 
          verification enabled:
            nx_secure_tls_process_remote_certificate.c
            nx_secure_tls_process_certificate_verify.c
            nx_secure_tls_remote_certificate_verify.c
            nx_secure_tls_server_handshake.c

        Files are modified to fix Session ID handling problem (session ID
          length is always 0 in the initial ServerHello):
            nx_secure_tls_send_serverhello.c

        Files are added to support new API for allocating buffer space
          for incoming remote certificates:
            nx_secure_tls_remote_certificate_buffer_allocate.c
            nxe_secure_tls_remote_certificate_buffer_allocate.c

        Files are modified to support new API for allocating buffer space
          for incoming remote certificates:
            nx_secure_tls.h
            nx_secure_tls_api.h

        Files are added to support new API for configuring Client X.509
          authentication for TLS servers:
            nx_secure_tls_session_x509_client_verify_configure.c
            nxe_secure_tls_session_x509_client_verify_configure.c

        Files are modified to support new API for Client X.509 authentication:
            nx_secure_tls.h
            nx_secure_tls_api.h

        Files are modified to clear cryptographic secret data on errors:
            nx_secure_tls_session_receive_records.c
            nx_secure_tls_session_send.c

        Files are modified to assure that random number values are always cast
          to 32-bit type or smaller:
            nx_secure_tls_generate_premaster_secret.c

        Files are modified to assure that CBC padding values are properly checked:
            nx_secure_tls_record_payload_decrypt.c

        Files are modified to assure that MAC hash checking happens even if
          decryption padding checking fails:
            nx_secure_tls_record_payload_decrypt.c
            nx_secure_tls_process_record.c

        Files are modified to free all allocated remote certificates in a
          TLS server session as soon as certificate chain validation is
          complete. TLS clients need the remote certificates until after
          the key echange is complete so they are cleared later:
            nx_secure_tls_process_remote_certificate.c
            nx_secure_tls_send_client_key_exchange.c

        Files are modified to fix the usage of crypto metadata for hash method:
            nx_secure_tls_local_certificate_add.c
            nx_secure_tls_process_remote_certificate.c
            nx_secure_tls_remote_certificate_verify.c
            nx_secure_tls_session_create.c
            nx_secure_tls_trusted_certificate_add.c
            nx_secure_x509.h
            nx_secure_x509_certificate_verify.c
            nx_secure_x509_crl_verify.c

        Files are modified to support AEAD cipher:
            nx_secure_tls.h
            nx_secure_tls_record_payload_decrypt.c
            nx_secure_tls_record_payload_encrypt.c

        Files are modified to reset TLS session state if the TLS connection fails:
            nx_secure_tls_session_end.c
            nx_secure_tls_session_start.c

        Files are modified to return errors if cryptographic routines are
          improperly initialized:
            nx_secure_tls.h
            nx_secure_tls_finished_hash_generate.c
            nx_secure_tls_process_finished.c

        Files are modified to support elliptic curve cryptography:
            nx_secure_tls.h
            nx_secure_tls_process_client_key_exchange.c
            nx_secure_tls_process_server_key_exchange.c
            nx_secure_tls_process_serverhello_extensions.c
            nx_secure_tls_send_client_key_exchange.c
            nx_secure_tls_send_clienthello_extensions.c
            nx_secure_tls_send_server_key_exchange.c
            nx_secure_tls_send_serverhello_extensions.c
            nx_secure_dtls_process_clienthello.c
            nx_secure_dtls_send_clienthello.c
            nx_secure_dtls_send_serverhello.c

        Files are added or modified to optimize the logic:
            nx_secure_tls_client_handshake.c
            nx_secure_tls_payload_encrypt.c
            nx_secure_tls_process_clienthello_extensions.c
            nx_secure_tls_process_record.c
            nx_secure_tls_send_certificate.c
            nx_secure_tls_send_certificate_verify.c
            nx_secure_tls_send_client_key_exchange.c
            nx_secure_tls_send_clienthello.c
            nx_secure_tls_send_clienthello_extensions.c
            nx_secure_tls_send_serverhello.c
            nx_secure_tls_send_serverhello_extensions.c
            nx_secure_tls_server_handshake.c
            nx_secure_tls_session_create.c
            nx_secure_x509.c
            nx_secure_x509_certificate_chain_verify.c

        Files are modified to add wait_option to _nx_secure_tls_send_certificate:
            nx_secure_dtls_client_handshake.c
            nx_secure_dtls_server_handshake.c
            nx_secure_tls.h
            nx_secure_tls_client_handshake.c
            nx_secure_tls_send_certificate.c
            nx_secure_tls_server_handshake.c

        Files are modified to fix renegotiation issue with certain browsers due to both
          SCSV and the Secure Renegotiation extension being required (should be either/or):
            nx_secure_tls.h
            nx_secure_tls_map_error_to_alert.c
            nx_secure_tls_process_clienthello.c
            nx_secure_tls_process_clienthello_extensions.c
            nx_secure_tls_process_serverhello_extensions.c
            nx_secure_tls_session_renegotiate.c
            nx_secure_tls_session_reset.c

        Files are modified about server state processing:
            nx_secure_tls_process_clienthello.c
            nx_secure_tls_process_client_key_exchange.c
            nx_secure_tls_process_finished.c
            nx_secure_tls_server_handshake.c
            nx_secure_dtls_server_handshake.c

        Files are modified to add flexibility of using macros instead of direct C library function calls:
            nx_secure_dtls_client_handshake.c
            nx_secure_dtls_hash_record.c
            nx_secure_dtls_packet_allocate.c
            nx_secure_dtls_process_clienthello.c
            nx_secure_dtls_process_clienthello.c
            nx_secure_dtls_process_header.c
            nx_secure_dtls_process_helloverifyrequest.c
            nx_secure_dtls_process_record.c
            nx_secure_dtls_send_clienthello.c
            nx_secure_dtls_send_helloverifyrequest.c
            nx_secure_dtls_send_record.c
            nx_secure_dtls_send_serverhello.c
            nx_secure_dtls_server_handshake.c
            nx_secure_dtls_session_cache.c
            nx_secure_dtls_session_create.c
            nx_secure_dtls_session_reset.c
            nx_secure_dtls_session_send.c
            nx_secure_dtls_verify_mac.c
            nx_secure_tls.h
            nx_secure_tls_client_handshake.c
            nx_secure_tls_client_psk_set.c
            nx_secure_tls_finished_hash_generate.c
            nx_secure_tls_generate_keys.c
            nx_secure_tls_generate_premaster_secret.c
            nx_secure_tls_key_material_init.c
            nx_secure_tls_local_certificate_remove.c
            nx_secure_tls_packet_allocate.c
            nx_secure_tls_process_certificate_verify.c
            nx_secure_tls_process_changecipherspec.c
            nx_secure_tls_process_clienthello.c
            nx_secure_tls_process_client_key_exchange.c
            nx_secure_tls_process_finished.c
            nx_secure_tls_process_remote_certificate.c
            nx_secure_tls_process_serverhello.c
            nx_secure_tls_process_serverhello_extensions.c
            nx_secure_tls_psk_add.c
            nx_secure_tls_psk_find.c
            nx_secure_tls_record_payload_encrypt.c
            nx_secure_tls_send_certificate_verify.c
            nx_secure_tls_send_clienthello.c
            nx_secure_tls_send_finished.c
            nx_secure_tls_send_serverhello.c
            nx_secure_tls_session_create.c
            nx_secure_tls_session_keys_set.c
            nx_secure_tls_session_reset.c
            nx_secure_tls_session_sni_extension_parse.c
            nx_secure_tls_verify_mac.c
            nx_secure_x509_certificate_initialize.c
            nx_secure_x509_certificate_revocation_list_parse.c
            nx_secure_x509_certificate_verify.c
            nx_secure_x509_crl_revocation_check.c
            nx_secure_x509_distinguished_name_compare.c
            nx_secure_x509_dns_name_initialize.c
            nx_secure_x509_oid_parse.c

        Files are modified to add extension hook:
            nx_secure_tls.h
            nx_secure_tls_generate_keys.c
            nx_secure_tls_generate_premaster_secret.c
            nx_secure_tls_process_certificate_request.c
            nx_secure_tls_process_certificate_verify.c
            nx_secure_tls_process_clienthello.c
            nx_secure_tls_process_clienthello_extensions.c
            nx_secure_tls_process_serverhello_extensions.c
            nx_secure_tls_process_server_key_exchange.c
            nx_secure_tls_send_certificate_request.c
            nx_secure_x509.h
            nx_secure_x509_crl_verify.c

        Files are modified to properly initialize the crypto control block and pass crypto handled
        into crypto internal functions:
            nx_secure_tls.h
            nx_secure_tls_finished_hash_generate.c
            nx_secure_tls_generate_keys.c
            nx_secure_tls_handshake_hash_init.c
            nx_secure_tls_handshake_hash_update.c
            nx_secure_tls_hash_record.c
            nx_secure_tls_process_certificate_verify.c
            nx_secure_tls_process_client_key_exchange.c
            nx_secure_tls_process_serverhello_extensions.c
            nx_secure_tls_process_server_key_exchange.c
            nx_secure_tls_record_hash_initialize.c
            nx_secure_tls_record_hash_update.c
            nx_secure_x509_certificate_verify.c
            nx_secure_x509_crl_verify.c

        Files are modified to clear encryption key and other secret data:
            nx_secure_dtls_send_record.c
            nx_secure_dtls_session_end.c
            nx_secure_dtls_session_receive.c
            nx_secure_dtls_session_start.c
            nx_secure_tls_client_handshake.c
            nx_secure_tls_finished_hash_generate.c
            nx_secure_tls_generate_keys.c
            nx_secure_tls_handshake_process.c
            nx_secure_tls_hash_record.c
            nx_secure_tls_process_certificate_verify.c
            nx_secure_tls_process_record.c
            nx_secure_tls_record_hash_calculate.c
            nx_secure_tls_record_payload_encrypt.c
            nx_secure_tls_send_record.c
            nx_secure_tls_session_receive.c
            nx_secure_tls_session_receive_records.c
            nx_secure_tls_session_renegotiate.c
            nx_secure_x509_crl_verify.c

        Files are added for crypto method self test:
            nx_secure_crypto_method_self_test_3des.c
            nx_secure_crypto_method_self_test_aes.c
            nx_secure_crypto_method_self_test_des.c
            nx_secure_crypto_method_self_test_hmac_md5.c
            nx_secure_crypto_method_self_test_hmac_sha.c
            nx_secure_crypto_method_self_test_md5.c
            nx_secure_crypto_method_self_test_prf.c
            nx_secure_crypto_method_self_test_rsa.c
            nx_secure_crypto_method_self_test_sha.c
            nx_secure_crypto_rng_self_test.c
            nx_secure_crypto_table_self_test.c
            nx_secure_crypto_table_self_test.h

        Other modified files:
            nx_secure_tls_finished_hash_generate.c          Fixed the function pointer checking.
            nx_secure_tls_send_record.c                     Skipped the hash when it was not required.
            nx_secure_tls_verify_mac.c                      Supported zero-length TLS application data records.
            nx_secure_x509.c                                Fixed issues with parsing offsets and
                                                              version check in parsing unique IDs.
            nx_secure_x509_certificate_revocation_list_parse.c
                                                            Improved CRL parsing.
            nx_secure_x509_certificate_initialize.c         Released mutex when return.
            nx_secure_x509_pkcs1_rsa_private_key_parse.c    Removed obsolete comment.

        Other added files:
            nx_secure_module_hash_compute.c                 Compute the hash value of module.
            nx_secure_tls_send_clienthello_extensions.c     Send ClientHello extensions.
            nx_secure_tls_send_serverhello_extensions.c     Send ServerHello extensions.
            nx_secure_tls_session_time_function_set.c       Set a function pointer to get the current time.
            nxe_secure_tls_session_time_function_set.c      Set a function pointer to get the current time.

        Files renamed:

               File Name in Release 5.11                             File Name in Release 5.11SP1
            nx_secure_tls_session_timestamp_function_set.c      nx_secure_tls_session_time_function_set.c
            nxe_secure_tls_session_timestamp_function_set.c     nxe_secure_tls_session_time_function_set.c


Copyright(c) 1996-2018 Express Logic, Inc.


Express Logic, Inc.
11423 West Bernardo Court
San Diego, CA  92127

www.expresslogic.com

