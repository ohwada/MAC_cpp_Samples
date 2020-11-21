/**
 * gnutls sample
 * 2020-07-01 K.OHWADA
 */

// TLS Client example with X.509 certificate support


// reference : https://gnutls.org/manual/html_node/Client-example-with-X_002e509-certificate-support.html#Client-example-with-X_002e509-certificate-support

/* This example code is placed in the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <gnutls/gnutls.h>
#include <gnutls/x509.h>
#include "http_socket.h"
#include "http_build.h"


/* A very basic TLS client, with X.509 authentication and server certificate
 * verification. Note that error recovery is minimal for simplicity.
 */

#define CHECK(x) assert((x)>=0)
#define LOOP_CHECK(rval, cmd) \
        do { \
                rval = cmd; \
        } while(rval == GNUTLS_E_AGAIN || rval == GNUTLS_E_INTERRUPTED); \
        assert(rval >= 0)


/** 
 * main
 */
int main(int argc, char *argv[])
{

// param
    const size_t MAX_BUF = 1024;
    char buffer[MAX_BUF + 1];

    char *host = "example.com";
    int port = 443;
    bool is_verify = true;

   if(argc == 4) {
      	host = argv[1];
      	port = atoi( argv[2] );
      	is_verify = (bool)atoi( argv[3] );
   } else if(argc == 3) {
      	host = argv[1];
      	port = atoi( argv[2] );
   } else if(argc == 2) {
      	host = argv[1];
    } else {
        fprintf(stderr, "Usage: %s  [host] [port] [verify] \n",  argv[0] );
    }

    fprintf(stderr, "host: %s \n",  host );
    fprintf(stderr, "port: %d \n",  port );
    fprintf(stderr, "verify: %d \n",  (int)is_verify );

    const char *CHECK_ERSION = "3.4.6";

        gnutls_session_t session;
        char *desc;
        gnutls_datum_t out;
        int type;
        unsigned status;
        gnutls_certificate_credentials_t xcred;


        if ( gnutls_check_version( (char *)CHECK_ERSION ) == NULL ) {
                fprintf(stderr, "GnuTLS 3.4.6 or later is required for this example\n");
                return EXIT_FAILURE;
        }


        /* for backwards compatibility with gnutls < 3.3.0 */
        CHECK(gnutls_global_init());

        /* X509 stuff */
        CHECK(gnutls_certificate_allocate_credentials(&xcred));

        /* sets the system trusted CAs for Internet PKI */
        CHECK(gnutls_certificate_set_x509_system_trust(xcred));

        /* If client holds a certificate it can be set using the following:
         *
         gnutls_certificate_set_x509_key_file (xcred, "cert.pem", "key.pem", 
         GNUTLS_X509_FMT_PEM); 
         */

        /* Initialize TLS session */
        CHECK(gnutls_init(&session, GNUTLS_CLIENT));


         CHECK(gnutls_server_name_set(session, GNUTLS_NAME_DNS,  host,
                                     strlen(host)));


        /* It is recommended to use the default priorities */
        CHECK(gnutls_set_default_priority(session));

        /* put the x509 credentials to the current session
         */
        CHECK(gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, xcred));


// verify
    if( is_verify) {
        unsigned flags = 0;
        gnutls_session_set_verify_cert(session, host, flags );
    }


// getaddrinfo
    struct addrinfo *info;
    char error[100];

 bool ret1 = get_addrinfo( (char *)host, (char *)SERVICE_HTTPS,  &info, (char *)error );

   if ( ret1) {
        print_addrinfo( info );
    } else {
        fprintf(stderr, "getaddrinfo: %s \n", error );
        return EXIT_FAILURE;
    }

// get IP addinfos
    char ipaddr[100];

    get_ipaddr_from_addrinfo(info, (char *)ipaddr);

    fprintf(stderr, "ipaddr: %s \n", ipaddr);


// open socket
    int socketfd;

    bool ret2 = open_socket( info, &socketfd, (char *)error );

    if(ret2){
        fprintf(stderr, "open_socket: %d \n", socketfd);
    } else {
        fprintf(stderr, "open_socket: %s \n", error);
        return EXIT_FAILURE;
    }


// connect host
    bool ret3 = connect_host( socketfd, (char *)ipaddr, port, (char *)error);

    if(ret3){
        fprintf(stderr, "Conntect to %s\n", (char *)host);
    } else {
        fprintf(stderr,  "connect_host: %s \n", (char *)error);
        goto label_error;
    }


        gnutls_transport_set_int(session, socketfd);

        gnutls_handshake_set_timeout(session,
                                     GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);

        /* Perform the TLS handshake
         */
      int ret;

        do {
                ret = gnutls_handshake(session);
        }
        while (ret < 0 && gnutls_error_is_fatal(ret) == 0);
        if (ret < 0) {
                if (ret == GNUTLS_E_CERTIFICATE_VERIFICATION_ERROR) {
                        /* check certificate verification status */
                        type = gnutls_certificate_type_get(session);
                        status = gnutls_session_get_verify_cert_status(session);
                        CHECK(gnutls_certificate_verification_status_print(status,
                              type, &out, 0));
                        printf("cert verify output: %s\n", out.data);
                        gnutls_free(out.data);
                }
                fprintf(stderr, "*** Handshake failed: %s\n", gnutls_strerror(ret));
                goto label_error;
        } else {
                desc = gnutls_session_get_desc(session);
                printf("- Session info: %s\n", desc);
                gnutls_free(desc);
        }

// create GET request 
    char request[500];

    build_http_root_path_request( (char *)host, (char *)request);

    fprintf(stderr, "%s \n", (char *)request );

	/* send data */
        LOOP_CHECK(ret, gnutls_record_send(session, request , strlen(request )) );

        LOOP_CHECK(ret, gnutls_record_recv(session, buffer, MAX_BUF));

        if (ret == 0) {
                printf("- Peer has closed the TLS connection\n");
                goto label_end;
        } else if (ret < 0 && gnutls_error_is_fatal(ret) == 0) {
                fprintf(stderr, "*** Warning: %s\n", gnutls_strerror(ret));
        } else if (ret < 0) {
                fprintf(stderr, "*** Error: %s\n", gnutls_strerror(ret));
                goto label_error;
        }

        if (ret > 0) {
                printf("--- Received %d bytes: \n", ret);
                for (int i = 0; i < ret; i++) {
                        fputc(buffer[i], stdout);
                }
                fputs("\n", stdout);
        }

        CHECK(gnutls_bye(session, GNUTLS_SHUT_RDWR));


// --- end ---
label_end:

        close_socket(socketfd);

        gnutls_deinit(session);

        gnutls_certificate_free_credentials(xcred);

        gnutls_global_deinit();

        fprintf(stderr, "successful \n");

        return EXIT_SUCCESS;


// --- error ---
label_error:

        close_socket(socketfd);

        gnutls_deinit(session);

        gnutls_certificate_free_credentials(xcred);

        gnutls_global_deinit();

        fprintf(stderr, "failed \n");

        return EXIT_FAILURE;
}


// Conntect to example.com
// --- Received 370 bytes: 
// HTTP/1.1 200 OK

