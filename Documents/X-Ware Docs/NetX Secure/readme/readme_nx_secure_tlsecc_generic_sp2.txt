Revision History

11/01/2018  NX Secure ECC generic code version 5.11SP2. This release includes the
            following major features:

            nx_secure_tls_ecc.h                             Added ECDSA algorithm to the signature algorithms extension.
            nx_secure_tls_ecc_clienthello_extensions.c      Added ECDSA algorithm to the signature algorithms extension.
            nx_secure_tls_ecc_process_certificate_request.c Fixed no client certificate handling.
            nx_secure_x509_ecc_certificate_revocation_list_parse.c
                                                            Fixed compiler errors when CRL was disabled.
            nx_secure_x509_ecc_crl_verify.c                 Fixed compiler errors when CRL was disabled.
            nx_secure_x509_ec_private_key_parse.c           Added buffer boundary checking in ASN.1 parsing.
            nx_secure_x509_ecc.c                            Added buffer boundary checking in ASN.1 parsing.

07/15/2018  Initial NX Secure ECC generic code version 5.11 SP1.


Copyright(c) 1996-2018 Express Logic, Inc.


Express Logic, Inc.
11423 West Bernardo Court
San Diego, CA  92127

www.expresslogic.com

