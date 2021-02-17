#pragma once
/**
 * openssl sample
 * 2021-02-01 K.OHWADA
 */

// verify X509 certificate 

// Feature equivalent to the command below
// openssl verify [-CApath directory] [-CAfile file] certificates
// https://www.openssl.org/docs/man1.0.2/man1/openssl-verify.html

// The certificates in the directory must be in hashed form, 

// reference : http://fm4dd.com/openssl/certverify.htm

/* ------------------------------------------------------------ *
 * file:        certverify.c                                    *
 * purpose:     Example code for OpenSSL certificate validation *
 * author:      06/12/2012 Frank4DD                             *
 *                                                              *
 * gcc -o certverify certverify.c -lssl -lcrypto                *
 * ------------------------------------------------------------ */

#include <stdio.h>
#include <stdbool.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>


// prototype
bool verfy_cert(char *file_cert,  char *file_cacert, char *dir_cacert );
bool print_subject_name(char *file_cert);


/**
 * verfy_cert
 */

bool verfy_cert(char *file_cert,  char *file_cacert, char *dir_cacert )
{

  BIO              *certbio = NULL;
  X509                *cert = NULL;
  X509_STORE         *store = NULL;
  X509_STORE_CTX  *ctx = NULL;

  /* ---------------------------------------------------------- *
   * These function calls initialize openssl for correct work.  *
   * ---------------------------------------------------------- */
  OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();

  /* ---------------------------------------------------------- *
   * Initialize the global certificate validation store object. *
   * ---------------------------------------------------------- */
    store = X509_STORE_new();
    if ( !store ) {
        ERR_print_errors_fp(stderr);
        return false;
    }

  /* ---------------------------------------------------------- *
   * Create the context structure for the validation operation. *
   * ---------------------------------------------------------- */
  ctx = X509_STORE_CTX_new();
    if ( !ctx ) {
        ERR_print_errors_fp(stderr);
        return false;
    }

  /* ---------------------------------------------------------- *
   * Load the certificate and cacert chain from file (PEM).     *
   * ---------------------------------------------------------- */
    certbio = BIO_new(BIO_s_file());
    BIO_read_filename(certbio, file_cert);
    cert = PEM_read_bio_X509(certbio, NULL, 0, NULL);

  if (!cert) {
    ERR_print_errors_fp(stderr);
    return false;
  }

// Note;
// The certificates in the directory must be in hashed form, 
    int ret1 = X509_STORE_load_locations(store, file_cacert, dir_cacert  );
    if (ret1 != 1) {
        ERR_print_errors_fp(stderr);
        return false;
    }

  /* ---------------------------------------------------------- *
   * Initialize the ctx structure for a verification operation: *
   * Set the trusted cert store, the unvalidated cert, and any  *
   * potential certs that could be needed (here we set it NULL) *
   * ---------------------------------------------------------- */
  X509_STORE_CTX_init(ctx, store, cert, NULL);

  /* ---------------------------------------------------------- *
   * Check the complete cert chain can be build and validated.  *
   * Returns 1 on success, 0 on verification failures, and -1   *
   * for trouble with the ctx object (i.e. missing certificate) *
   * ---------------------------------------------------------- */
  int ret2 = X509_verify_cert(ctx);

if(ret2<= 0) {
        int ctx_err =  X509_STORE_CTX_get_error(ctx);
        const char *str_err = X509_verify_cert_error_string(ctx_err);
        printf("%s \n", str_err);
       ERR_print_errors_fp(stderr);
}

  /* ---------------------------------------------------------- *
   * Free up all structures                                     *
   * ---------------------------------------------------------- */
  X509_STORE_CTX_free(ctx);
  X509_STORE_free(store);
  X509_free(cert);
  BIO_free_all(certbio);

    bool res = (ret2 == 1)? true: false;
    return res;
}


/**
 * print_subject_name
 */
bool print_subject_name(char *file_cert)
{

  BIO *certbio = NULL;
  X509  *cert = NULL;
  X509_NAME  *certsubject = NULL;


//  Load the certificate from file (PEM).    
  certbio = BIO_new(BIO_s_file());
  BIO_read_filename(certbio, file_cert);
  cert = PEM_read_bio_X509(certbio, NULL, 0, NULL);

  if (!cert) {
    ERR_print_errors_fp(stderr);
    return false;
  }

// print subject name
    certsubject = X509_get_subject_name(cert);
    X509_NAME_print_ex_fp( stdout, certsubject, 0, XN_FLAG_MULTILINE);
    printf("\n");

// Free up all structures   
    X509_free(cert);
    BIO_free_all(certbio);

    return true;
}


