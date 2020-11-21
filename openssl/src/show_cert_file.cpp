/**
 * openssl sample
 * 2020-07-01 K.OHWADA
 */


// show SSL certificate info from file

// g++ show_cert_file.cpp  -std=c++11 `pkg-config --cflags --libs openssl` 

// reference : https://gist.github.com/cseelye/adcd900768ff61f697e603fd41c67625


#include <iostream>
#include <memory>
#include <string>
#include <cstring>
#include <ctime>
#include <openssl/asn1.h>
#include <openssl/bio.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>


// Smart pointers to wrap openssl C types that need explicit free
using BIO_ptr = std::unique_ptr<BIO, decltype(&BIO_free)>;
using X509_ptr = std::unique_ptr<X509, decltype(&X509_free)>;
using ASN1_TIME_ptr = std::unique_ptr<ASN1_TIME, decltype(&ASN1_STRING_free)>;


// Convert the contents of an openssl BIO to a std::string
std::string bio_to_string(const BIO_ptr& bio, const int& max_len)
{
    // We are careful to do operations based on explicit lengths, not depending
    // on null terminated character streams except where we ensure the terminator

    // Create a buffer and zero it out
    char buffer[max_len];
    memset(buffer, 0, max_len);
    // Read one smaller than the buffer to make sure we end up with a null
    // terminator no matter what
    BIO_read(bio.get(), buffer, max_len - 1);
    return std::string(buffer);
}


/**
 * getSubject
 */
std::string getSubject(X509 *cert)
{

    BIO_ptr output_bio(BIO_new(BIO_s_mem()), BIO_free);

    X509_NAME *subject_name = X509_get_subject_name( cert );
    if(!subject_name){
        std::cout << "X509_get_subject_name faied: " << std::endl;
        ERR_print_errors_fp(stderr);
    }

    // Print the subject into a BIO and then get a string
    X509_NAME_print_ex(output_bio.get(), subject_name, 0, 0);

    return bio_to_string(output_bio, 4096);
}


/**
 * getIssuer
 */
std::string getIssuer(X509 *cert)
{

    BIO_ptr output_bio(BIO_new(BIO_s_mem()), BIO_free);

    X509_NAME *issuer_name = X509_get_issuer_name( cert );
    if(!issuer_name){
        std::cout << "X509_get_issuer_name faied: " << std::endl;
        ERR_print_errors_fp(stderr);
    }


    X509_NAME_print_ex(output_bio.get(), issuer_name, 0, 0);

    return bio_to_string(output_bio, 4096);

}


/**
 * getExpiretime
 */
std::string getExpireTime(X509 *cert)
{

    ASN1_TIME *expires = X509_get_notAfter(cert);
    if(!expires){
        std::cout << "X509_get_notAfter faied: " << std::endl;
        ERR_print_errors_fp(stderr);
    }

// formst to string
    const char* FORMAT = "%Y-%m-%d %H:%M:%S %Z";

    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

    std::tm asn1;

    int ret2 = ASN1_TIME_to_tm(expires, &asn1);
    if(ret2 != 1){
        std::cout << "ASN1_TIME_to_tm faied: " << std::endl;
        ERR_print_errors_fp(stderr);
    }

    time_t time = std::mktime( &asn1 );
    std::tm *tm = std::localtime( &time );

    std::strftime( buf, BUFSIZE, (char *)FORMAT, tm );

    return std::string(buf);
}


/**
 * main
 */
int main(int argc, char** argv)
{

    std::string file;

    if (argc == 2){
        file = argv[1];
    } else {
        std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "file: " << file << std::endl;


// ssl
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    OPENSSL_no_config();

    BIO_ptr input( BIO_new(BIO_s_file()), BIO_free );

    int ret1 = BIO_read_filename( input.get(), file.c_str() );
 
    if (ret1 != 1) {
        std::cout << "BIO_read_filename faied: " << file << std::endl;
        ERR_print_errors_fp(stderr);
        return EXIT_FAILURE;
    }


// Create an openssl certificate from the BIO
    X509_ptr cert(PEM_read_bio_X509_AUX(input.get(), NULL, NULL, NULL), X509_free);


// subject
    std::string subject = getSubject( cert.get() );

    std::cout << std::endl;
    std::cout << "Subject:" << std::endl;
    std::cout << subject << std::endl;
    std::cout << std::endl;

// Issuer
    std::string issuer = getIssuer( cert.get() );

    std::cout << "Issuer:" << std::endl;
    std::cout << issuer << std::endl;
    std::cout << std::endl;

// expire
    std::string expire = getExpireTime( cert.get() );

    std::cout << "Expire: " << expire << std::endl;
    std::cout << std::endl;


    FIPS_mode_set(0);
    CONF_modules_unload(1);
    CONF_modules_free();
    ERR_free_strings();
    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();


    return EXIT_SUCCESS;
}
