/**
 * http_server.h
 * 2022-06-01 K.OHWADA
 */

// HTTPS Server

// reference : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/https_fileserver_example.c


#include <gnutls/gnutls.h>
#include <gcrypt.h>
#include "server.h"
#include "file_util.h"


// prototype
bool run_https_server_file(int port, char* file_key, char* file_cert);
bool run_https_server_pem(int port, char* key_pem, char* cert_pem);


/**
 * run_https_server
 */
bool run_https_server_file(int port, char* file_key, char* file_cert)
{

    const size_t BUFSIZE = 512;
    char error[ BUFSIZE];

size_t size_key;
size_t size_cert;

// 10,722 Bytes
char* key_pem = file_text_read1( file_key, &size_key, (char *)error );
    if(!key_pem){
        fprintf(stderr, "read file error: %s: %s \n", file_key, error );
        return false;
    }

printf("size_key: %zu \n", size_key );

// 2,049 Bytes
 char* cert_pem = file_text_read1( (char *)file_cert, &size_cert, (char *)error );
    if(!cert_pem){
        fprintf( stderr, "read file error: %s: %s \n", file_cert, error );
        return false;
    }


printf("size_cert: %zu \n", size_cert );

    //return run_https_server_pem(port, (char *)key_pem, (char *)cert_pem );
    bool ret = run_https_server_pem(port, key_pem, cert_pem );
    free(key_pem);
    free(cert_pem);
    return ret;
}


/**
 * run_https_server
 */
bool run_https_server_pem(int port, char* key_pem, char* cert_pem)
{

  struct MHD_Daemon *TLS_daemon;

      TLS_daemon =
        MHD_start_daemon (MHD_USE_THREAD_PER_CONNECTION | 
        MHD_USE_INTERNAL_POLLING_THREAD |
        MHD_USE_DEBUG |
                          MHD_USE_SSL, port, NULL, NULL, (void *)&ahc_echo,
                          NULL, MHD_OPTION_CONNECTION_TIMEOUT, 256,
                          MHD_OPTION_HTTPS_MEM_KEY, key_pem,
                          MHD_OPTION_HTTPS_MEM_CERT, cert_pem,
                          MHD_OPTION_END);


  if (TLS_daemon == NULL)
    {
      fprintf (stderr, "Error: failed to start TLS_daemon\n");
      return false;
    }
  
    printf ("listening on port %d\n", port );
    
  printf("enter return key to qiut \n");

  (void) getc (stdin);

  MHD_stop_daemon (TLS_daemon);

    return true;
}
