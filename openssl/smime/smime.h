#pragma once
/**
 * openssl sample
 * 2021-02-01 K.OHWADA
 */

// function for openssl smime

// TODO:
// return error message as string
// instead of displaying it on the display


// reference : https://git.ichec.ie/performance/storage/superdeimos/-/blob/8e8b7947046f6a54b7c2d4bd6af30657c4042315/external/openssl/demos/smime/smenc.c

/*
 * Copyright 2007-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdbool.h>
#include <openssl/pem.h>
#include <openssl/pkcs7.h>
#include <openssl/err.h>


// prototype
bool smime_encrypt_stream(char  *input , char *output, char *recpt_publc );
bool smime_sign_stream_detached( char *input, char *output, char *signer_cert,  char *signer_key );
bool smime_encrypt(char  *input , char *output, char *recpt_publc, int flags );
bool smime_decrypt(char *input, char *output, char *recpt_cert, char *recpt_key, int flags );
bool smime_sign( char *input, char *output, char *signer_cert,  char *signer_key, int flags );
bool smime_verify( char *input, char *output, char *signer_cert, int flags );


    /*
     * For simple S/MIME signing use PKCS7_DETACHED. On OpenSSL 0.9.9 only:
     * for streaming detached set PKCS7_DETACHED|PKCS7_STREAM for streaming
     * non-detached set PKCS7_STREAM
     */
    int sign_flags = PKCS7_DETACHED | PKCS7_STREAM;


/**
 * encrypt
 */
bool smime_encrypt_stream(char  *input , char *output, char *recpt_publc )
{

// On OpenSSL 0.9.9 only:
  // for streaming set PKCS7_STREAM
// if the PKCS7_STREAM flag is set 
// a partial PKCS7 structure is output suitable for streaming I/O
    int flags = PKCS7_STREAM;


    return smime_encrypt( input , output, recpt_publc, flags );

}


/**
 * sign
 */
bool smime_sign_stream_detached( char *input, char *output, char *signer_cert,  char *signer_key )
{

// For simple S/MIME signing use PKCS7_DETACHED. 
// On OpenSSL 0.9.9 only:
// for streaming detached set PKCS7_DETACHED|PKCS7_STREAM for streaming
// non-detached set PKCS7_STREAM
    int flags = PKCS7_DETACHED | PKCS7_STREAM;

    return smime_sign( input, output, signer_cert,  signer_key, flags );
}


/**
 * encrypt
 */
bool smime_encrypt(char  *input , char *output, char *recpt_publc, int flags )
{

    BIO *in = NULL, *out = NULL, *tbio = NULL;
    X509 *rcert = NULL;
    STACK_OF(X509) *recips = NULL;
    PKCS7 *p7 = NULL;
    bool is_error = false;

    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    /* Read in recipient certificate */
    tbio = BIO_new_file( recpt_publc, "r");

    if (!tbio) {
        is_error = true;
        goto err;
    }

    rcert = PEM_read_bio_X509(tbio, NULL, 0, NULL);

    if (!rcert) {
        is_error = true;
        goto err;
    }

    /* Create recipient STACK and add recipient cert to it */
    recips = sk_X509_new_null();

    if (!recips || !sk_X509_push( recips, rcert ) ) {
        is_error = true;
        goto err;
    }

    /*
     * sk_X509_pop_free will free up recipient STACK and its contents so set
     * rcert to NULL so it isn't freed up twice.
     */
    rcert = NULL;

    /* Open content being encrypted */

    in = BIO_new_file( input , "r" );

    if (!in) {
        is_error = true;
        goto err;
    }

    /* encrypt content */
    p7 = PKCS7_encrypt(recips, in, EVP_des_ede3_cbc(), flags);

    if (!p7) {
        is_error = true;
        goto err;
    }

    out = BIO_new_file( output, "w" );
    if (!out) {
        is_error = true;
        goto err;
    }

    /* Write out S/MIME message */
    int ret = SMIME_write_PKCS7(out, p7, in, flags);

    if( ret == 0 ) {
        is_error = true;
        goto err;
    }

 err:
    if ( is_error ) {
        fprintf(stderr, "Error Encrypting Data \n");
        ERR_print_errors_fp(stderr);
    }

    PKCS7_free(p7);
    X509_free(rcert);
    sk_X509_pop_free(recips, X509_free);
    BIO_free(in);
    BIO_free(out);
    BIO_free(tbio);

    return !is_error;

}


/**
 * decrypt
 */
bool smime_decrypt(char *input, char *output, char *recpt_cert, char *recpt_key, int flags )
{
    BIO *in = NULL, *out = NULL, *tbio_cert = NULL, *tbio_key = NULL ;
    X509 *rcert = NULL;
    EVP_PKEY *rkey = NULL;
    PKCS7 *p7 = NULL;
    bool is_error = false;


    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    /* Read in recipient certificate and private key */
    tbio_cert = BIO_new_file( recpt_cert, "r" );

    if (!tbio_cert) {
        is_error = true;
        goto err;
    }

    tbio_key = BIO_new_file( recpt_key, "r" );

    if (!tbio_key) {
        is_error = true;
        goto err;
    }

    rcert = PEM_read_bio_X509(tbio_cert, NULL, 0, NULL);

    // BIO_reset(tbio);

    rkey = PEM_read_bio_PrivateKey(tbio_key, NULL, 0, NULL);

    if (!rcert || !rkey) {
        is_error = true;
        goto err;
    }

    /* Open content being signed */

    in = BIO_new_file( input, "r" );

    if (!in) {
        is_error = true;
        goto err;
    }

    /* Sign content */
    p7 = SMIME_read_PKCS7(in, NULL);

    if (!p7) {
        is_error = true;
        goto err;
    }

    out = BIO_new_file( output, "w" );
    if (!out) {
        is_error = true;
        goto err;
    }

    /* Decrypt S/MIME message */
    int ret = PKCS7_decrypt(p7, rkey, rcert, out, flags);

    if ( ret == 0) {
        is_error = true;
        goto err;
    }


 err:
    if ( is_error ) {
        fprintf(stderr, "Error Signing Data \n");
        ERR_print_errors_fp(stderr);
    }

    PKCS7_free(p7);
    X509_free(rcert);
    EVP_PKEY_free(rkey);
    BIO_free(in);
    BIO_free(out);
    BIO_free(tbio_cert);
    BIO_free(tbio_key);

    return !is_error;
}


/**
 * sign
 */
bool smime_sign( char *input, char *output, char *signer_cert,  char *signer_key, int flags )
{

    BIO *in = NULL, *out = NULL, *tbio_cert = NULL, *tbio_key = NULL;

    X509 *scert = NULL;
    EVP_PKEY *skey = NULL;
    PKCS7 *p7 = NULL;
    bool is_error = false;



    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    /* Read in signer certificate and private key */
    tbio_cert = BIO_new_file( signer_cert, "r" );

    if (!tbio_cert) {
         is_error = true;
        goto err;
    }

    tbio_key = BIO_new_file( signer_key, "r" );

    if (!tbio_key) {
         is_error = true;
        goto err;
    }

    scert = PEM_read_bio_X509(tbio_cert, NULL, 0, NULL);

    //BIO_reset(tbio);

    skey = PEM_read_bio_PrivateKey(tbio_key, NULL, 0, NULL);

    if (!scert || !skey) {
         is_error = true;
        goto err;
    }

    /* Open content being signed */

    in = BIO_new_file( input, "r" );

    if (!in) {
         is_error = true;
        goto err;
    }

    /* Sign content */
    p7 = PKCS7_sign( scert, skey, NULL, in, flags );

    if (!p7) {
         is_error = true;
        goto err;
    }

    out = BIO_new_file( output, "w" );

    if (!out) {
         is_error = true;
        goto err;
    }

    if (!(flags & PKCS7_STREAM)) {
        BIO_reset(in);
    }

    /* Write out S/MIME message */
    int ret = SMIME_write_PKCS7( out, p7, in, flags );

    if ( ret == 0){
         is_error = true;
        goto err;
    }

 err:
    if (is_error) {
        fprintf(stderr, "Error Signing Data\n");
        ERR_print_errors_fp(stderr);
    }

    PKCS7_free(p7);
    X509_free(scert);
    EVP_PKEY_free(skey);
    BIO_free(in);
    BIO_free(out);
    BIO_free(tbio_cert);
    BIO_free(tbio_key);

    return !is_error;

}



/**
 * verify
 */
bool smime_verify( char *input, char *output, char *signer_cert, int flags )
{

    BIO *in = NULL, *out = NULL, *tbio = NULL, *cont = NULL;
    X509_STORE *st = NULL;
    X509 *scert = NULL;
    PKCS7 *p7 = NULL;

    bool is_error = false;

    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    /* Set up trusted CA certificate store */

    st = X509_STORE_new();

    /* Read in signer certificate and private key */
    tbio = BIO_new_file( signer_cert, "r" );

    if (!tbio) {
        is_error = true;
        goto err;
    }

    scert = PEM_read_bio_X509( tbio, NULL, 0, NULL );

    if (!scert) {
        is_error = true;
        goto err;
    }

    int ret1 = X509_STORE_add_cert(st, scert);

    if ( ret1 == 0 ) {
        is_error = true;
        goto err;
    }

    /* Open content being signed */

    in = BIO_new_file( input, "r" );

    if (!in) {
        is_error = true;
        goto err;
    }

    /* Sign content */
    p7 = SMIME_read_PKCS7(in, &cont);

    if (!p7) {
        is_error = true;
        goto err;
    }

    /* File to output verified content to */
    out = BIO_new_file( output, "w" );

    if (!out) {
        is_error = true;
        goto err;
    }

    int ret2 = PKCS7_verify(p7, NULL, st, cont, out, flags);

    if ( ret2 == 0 ) {
        is_error = true;
        fprintf(stderr, "Verification Failure\n");
        goto err;
    }

 err:
    if (is_error) {
        fprintf(stderr, "Error Verifying Data\n");
        ERR_print_errors_fp(stderr);
    }

    PKCS7_free(p7);
    X509_free(scert);
    BIO_free(in);
    BIO_free(out);
    BIO_free(tbio);

    return !is_error;
}
