/**
 * local_server.c
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/rboulton/libmicrohttpd/blob/master/src/examples/querystring_example.c

#include "mhd_server.h"
#include "index_html.h"
#include "auth_code.h"
 #include  "refresh_token.h"
#include "config.h"


// global
bool is_debug = false;


/**
 * on_listen
 */
void on_listen()
{
    pleaseEnterAuthorizationCode();
}


/**
 * ahc_echo
 */
int ahc_echo (void *cls,
          struct MHD_Connection *connection,
          const char *url,
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr)
{

  const char* FORMAT =  "<html><head></head><body><h1>Local Server</h1><font size='+2'>code<br/>|%s| <br/>scope<br/>|%s|<br/></font></body></html>";

    const size_t BUFSIZE = 1024;
    char buf[BUFSIZE];
    char text[BUFSIZE];
    char error[BUFSIZE];
    char request[BUFSIZE];

    char* mime= "text/html";

  static int aptr;

    printf("\n method: %s \n", method);
    printf("url: %s \n", url);

    if ( strcmp(method, "GET") != 0) {
        return MHD_NO;
    }

  if (&aptr != *ptr)
    {
      /* do never respond on first call */
      *ptr = &aptr;
      return MHD_YES;
    }

  *ptr = NULL;                  /* reset when done */

    const char* Q1 = "code" ;
    const char* Q2 = "scope" ;
    const char *code;
    const char *scope;


code = MHD_lookup_connection_value (connection, MHD_GET_ARGUMENT_KIND, Q1);

scope = MHD_lookup_connection_value (connection, MHD_GET_ARGUMENT_KIND, Q2);


printf("code %s \n", code);
printf("scope %s \n", scope);

    if ( (code == NULL)||(scope == NULL) )
    {
        bool ret2 = get_index_html( (char *)text, (char *)error );
        if(ret2) {
            return response_text_copy( connection, text, mime);
        }else{
            fprintf(stderr, "get_index_html faild: %s", error);
            return MHD_NO;
        }
    }

    snprintf (buf, BUFSIZE, FORMAT, code, scope);

    printf("buf: %s \n", buf);

    int ret3 = response_text_copy( connection, buf, mime);

    buildRefreshTokenRequest( (char *)code, (char *)request);

    printf("\n request \n");
    printf("%s \n", request);

 if( is_debug ) {
    return ret3;
}

    bool  ret4 = requestRefreshTokenToFile( (char *)request, (char *)error );

    if(ret4){
        printf("requestRefreshTokenToFile successful \n");
    } else{
        fprintf(stderr, "requestRefreshTokenToFile faild: %s \n", error);
    }

    return ret3;
}


/**
 * main
 */
int main (int argc, char *const *argv)
{

    if(argc == 2) {
      	is_debug = (bool)atoi(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s  [debug] \n",  argv[0] );
    }

    if( is_debug ) {
        printf("debug mode \n");
    }

    run_server(PORT);

    return 0;
}
