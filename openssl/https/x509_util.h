#pragma once
/**
 * openssl sample
 * 2021-02-01 K.OHWADA
 */

// openssl X509 utility

// reference : https://wiki.openssl.org/index.php/SSL/TLS_Client#Verification


// TODO:
// save x509
// suport output pem format


#include <stdio.h>
#include <errno.h> 
#include  <string.h>
#include <openssl/x509v3.h>



// prototype
bool get_x509_subject_name( X509 *cert,  char *subject );
bool get_x509_issuer_name( X509 *cert,  char *issuer );
bool get_x509_cmmon_name( X509_NAME *name, char *cn );
void print_x509_san_names( const X509 *cert );
bool save_x509_to_der( X509 *cert,  char *subject );
void  replace_char_all( char *src, char *result, char target, char replace);


/**
 * get_x509_subject_name
 */
bool get_x509_subject_name( X509 *cert,  char *subject )
{

    X509_NAME *sname = X509_get_subject_name(cert);

    if(!sname){
        ERR_print_errors_fp(stderr);
        return false;
    }

    return get_x509_cmmon_name( sname, subject );
}


/**
 * get_x509_ssuer_name
 */
bool get_x509_issuer_name( X509 *cert,  char *issuer )
{

  X509_NAME *iname = X509_get_issuer_name(cert);
   
    if(!iname){
        ERR_print_errors_fp(stderr);
        return false;
    }

    return get_x509_cmmon_name( iname, issuer );
}


/**
 * get_x509_cmmon_name
 */
bool get_x509_cmmon_name( X509_NAME *name, char *cn )
{

    int idx = -1;

    unsigned char *utf8 = NULL;

    bool success = false;

    do
    {
        if(!name) {
            break; /* failed */
        }

        idx = X509_NAME_get_index_by_NID(name, NID_commonName, -1);

        if(!(idx > -1))  {
            ERR_print_errors_fp(stderr);    
            break; /* failed */
        }
        
        X509_NAME_ENTRY* entry = X509_NAME_get_entry(name, idx);

        if(!entry) {
        ERR_print_errors_fp(stderr);
            break; /* failed */
        }

        ASN1_STRING* data = X509_NAME_ENTRY_get_data(entry);

        if(!data) {
             ERR_print_errors_fp(stderr);
            break; /* failed */
        }

        int length = ASN1_STRING_to_UTF8(&utf8, data);

        if(!utf8 || !(length > 0)) {
            ERR_print_errors_fp(stderr);
            break; /* failed */
        }

        strcpy( cn, (char *)utf8 );
        success = true;
        
    } while (0);
    
    if(utf8) {
        OPENSSL_free(utf8);
    }

    return success;
}



/**
 * save_x509_to_der
 */
bool save_x509_to_der( X509 *cert,  char *subject )
{

// TODO:
// suport output pem format

    const char BLANK = ' ';
    const char UNDERBAR = '_';

    const size_t BUFSIZE = 100;
    char file[BUFSIZE];

    char FORMAT[] = "%s.der";

    bool success = false;

    char fname[100];

    replace_char_all( subject, (char *)fname, BLANK, UNDERBAR );

    snprintf( file, BUFSIZE,  (char *)FORMAT, fname );

// file open with write binary mode
    FILE *fp = fopen(file, "wb");

    if(!fp){
        int saved_errno = errno;
        printf( "open faild: %s: %s \n", file, strerror(saved_errno) );
        return false;
    }

// save
    int ret = i2d_X509_fp(fp, cert);

    if(ret > 0 ) {
        printf("saved to: %s \n", file);
        success = true;;
    } else {
        printf("i2d_X509_fp faild: %s \n", file);
        ERR_print_errors_fp(stderr);
    }

    fclose(fp);

    return success;
}


/**
 *   replace_char_all
 */

void  replace_char_all( char *src, char *result, char target, char replace)
{

    char *p;

    strcpy(result, src);

    while ( (p = strchr(result, target)) != NULL ) {
        *p = replace;
    }
}



/**
 * print_cn_name
 */
void print_cn_name(const char* label, X509_NAME* const name)
{
    int idx = -1, success = 0;
    unsigned char *utf8 = NULL;
    
    do
    {
        if(!name) break; /* failed */
        
        idx = X509_NAME_get_index_by_NID(name, NID_commonName, -1);
        if(!(idx > -1))  break; /* failed */
        
        X509_NAME_ENTRY* entry = X509_NAME_get_entry(name, idx);
        if(!entry) break; /* failed */
        
        ASN1_STRING* data = X509_NAME_ENTRY_get_data(entry);
        if(!data) break; /* failed */
        
        int length = ASN1_STRING_to_UTF8(&utf8, data);
        if(!utf8 || !(length > 0))  break; /* failed */
        
        fprintf(stdout, "  %s: %s\n", label, utf8);
        success = 1;
        
    } while (0);
    
    if(utf8)
        OPENSSL_free(utf8);
    
    if(!success)
        fprintf(stdout, "  %s: <not available>\n", label);
}


/**
 * print_x509_san_names
 */
void print_x509_san_names(const X509 *cert)
{
    int success = 0;
    GENERAL_NAMES* names = NULL;
    unsigned char* utf8 = NULL;
    
    do
    {
        if(!cert) break; /* failed */
        
        names = X509_get_ext_d2i(cert, NID_subject_alt_name, 0, 0 );
        if(!names) break;
        
        int i = 0, count = sk_GENERAL_NAME_num(names);
        if(!count) break; /* failed */
        
        for( i = 0; i < count; ++i )
        {
            GENERAL_NAME* entry = sk_GENERAL_NAME_value(names, i);
            if(!entry) continue;
            
            if(GEN_DNS == entry->type)
            {
                int len1 = 0, len2 = -1;
                
                len1 = ASN1_STRING_to_UTF8(&utf8, entry->d.dNSName);
                if(utf8) {
                    len2 = (int)strlen((const char*)utf8);
                }
                
                if(len1 != len2) {
                    fprintf(stderr, "  Strlen and ASN1_STRING size do not match (embedded null?): %d vs %d\n", len2, len1);
                }
                
                /* If there's a problem with string lengths, then     */
                /* we skip the candidate and move on to the next.     */
                /* Another policy would be to fails since it probably */
                /* indicates the client is under attack.              */
                if(utf8 && len1 && len2 && (len1 == len2)) {
                    fprintf(stdout, "%d : %s\n", (i+1), utf8);
                    success = 1;
                }
                
                if(utf8) {
                    OPENSSL_free(utf8), utf8 = NULL;
                }
            }
            else
            {
                fprintf(stderr, "  Unknown GENERAL_NAME type: %d\n", entry->type);
            }
        }

    } while (0);
    
    if(names)
        GENERAL_NAMES_free(names);
    
    if(utf8)
        OPENSSL_free(utf8);
        
}

