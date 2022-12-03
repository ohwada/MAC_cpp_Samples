/**
 * show_values.c
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/Ki4mTaria/items/d73cf3d244c903d493eb

#include <stdio.h>
#include <stdlib.h>
#include <hiredis.h>


/**
 * main
 */
int main(void)
{
  redisContext *conn = NULL;
  redisReply *resp   = NULL;
  int loop           = 0;

// Destination redis server
char* host = "127.0.0.1";

int port = 6379;     

 // connect
  conn = redisConnect( host ,  port);

  if( NULL == conn ){
    fprintf(stderr, "redisConnect failed \n");
    return EXIT_FAILURE;
  } else if ( conn->err ) {
    fprintf(stderr, "redisConnect: %s \n" , conn->errstr );
    redisFree( conn );
    return EXIT_FAILURE;
}

// Get Values
  for( loop=1 ; loop < 4 ; loop++ ) {
    resp = (redisReply *) redisCommand( conn , 
                                        "GET %d" , loop // command
                                      );
    if( NULL == resp ){
        fprintf(stderr, "redisCommand failed \n");
        redisFree( conn );
        return EXIT_FAILURE;
    }
    if( REDIS_REPLY_ERROR == resp->type ){
        fprintf(stderr, "redisCommand failed \n");
        redisFree( conn );
        freeReplyObject( resp );
          return EXIT_FAILURE;
    }
    printf( "%d : %s \n" , loop , resp->str );
    freeReplyObject( resp );

  } // for

// clean up
  redisFree( conn );

    return EXIT_SUCCESS;
}

// 1 : aaa
// 2 : bbb
// 3 : ccc

