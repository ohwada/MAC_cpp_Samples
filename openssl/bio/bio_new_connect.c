/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */

// connect Google using BIO_new_connect

// reference : https://bg1.hatenablog.com/entry/2017/05/19/210000


#include <openssl/bio.h>
#include <openssl/err.h>


/**
 * main
 */
int main(void)
{

    const char URL[] = "www.google.com:443";

    BIO *bio = NULL;

// open BIO and connect to URL
  bio = BIO_new_connect(URL); 

  if (bio == NULL){
    // failed
    printf("BIO_new_connect faild: %s \n", URL);
    return -1;
  }

// success to connect
    printf("conected: %s \n", URL);
    printf("bio = %08x\n", bio); 

// close and release BIO
  BIO_free_all(bio);

  return 0; 
}
