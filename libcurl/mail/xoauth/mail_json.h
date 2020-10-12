#pragma once
/**
 * libcurl Sample
 * 2020-07-01 K.OHWADA
 */

// parse mail json file


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <json.h>


/**
 * struct MailParam
 */
struct MailParam {
char* smtp_url;
char* smtp_server;
int smtp_port;
char* pop_url;
char* imap_url;
char* user;
char* passwd;
char* to;
char* from;
};


// prototype
char* getHomeDir(void);
char* getMailDir(void);
 struct MailParam getGmailParam(void);
struct MailParam getUbuntuMailParam(void);
struct MailParam getMailParam(char* filepath);
void parseMailJson(struct json_object* const obj, 
char* smtp_url, char* smtp_server, int* smtp_port, char* pop_url, char* imap_url, char* user, char* passwd, char* to, char* from) ;
void printMailParam(struct MailParam p);


/**
 *  getHomeDir
 */
char* getHomeDir(void)
{
    const size_t BUFSIZE = 100;
    static char buf[BUFSIZE];

    char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    strcpy(buf,  homedir );
    return buf;
}


/**
 *  getMailDir
 */
char* getMailDir(void)
{
    const size_t BUFSIZE = 100;
    static char buf[BUFSIZE];

    strcpy( buf, getHomeDir() );
    strcat( buf, "/mail");

    return buf;
}


/**
 * getGmailParam
 */
 struct MailParam getGmailParam(void) 
{
    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

    strcpy( buf, getMailDir() );
    strcat( buf, "/gmail.json");

    return getMailParam(buf);
}

/**
 * getUbuntuMailParam
 */
struct MailParam getUbuntuMailParam(void) 
{
    const size_t BUFSIZE = 100;
    char buf[BUFSIZE];

    strcpy( buf, getMailDir() );
    strcat( buf, "/ubuntu.json");

    return getMailParam(buf);
}


/**
 * getMailParam
 */
struct MailParam getMailParam(char* filepath)
{
    const size_t MEMSIZE = 100;
  
    static struct MailParam p;

    char* smtp_url = (char *)malloc(MEMSIZE);
    char* smtp_server = (char *)malloc(MEMSIZE);
    char* pop_url = (char *)malloc(MEMSIZE);
    char* imap_url = (char *)malloc(MEMSIZE);
    char* user = (char *)malloc(MEMSIZE);
    char* passwd = (char *)malloc(MEMSIZE);
    char* to = (char *)malloc(MEMSIZE);
    char* from = (char *)malloc(MEMSIZE);
    int smtp_port;

    struct json_object *jobj_from_file = json_object_from_file(filepath);

    if (json_object_is_type(jobj_from_file, json_type_null)) {
        printf( "json_object_from_file faild: %s \n", filepath );
        return p;
    }

    parseMailJson(jobj_from_file, 
    smtp_url, smtp_server, &smtp_port, pop_url, imap_url, user, passwd, to, from );

    p.smtp_url = smtp_url;
    p.smtp_server = smtp_server;
    p.smtp_port = smtp_port;
    p.pop_url = pop_url;
    p.imap_url = imap_url;
    p.user = user;
    p.passwd = passwd;
    p.to = to;
    p.from = from;

    return p;
}


/**
 * parseMailJson
 */
void parseMailJson(struct json_object* const obj, 
char* smtp_url,  char* smtp_server, int* smtp_port, char* pop_url, char* imap_url, char* user, char* passwd, char* to, char* from) 
{

    json_object_object_foreach(obj, key, val) {
  
            if (strcmp(key, "smtp_url") == 0) { 
                strcpy(smtp_url, json_object_get_string(val) );
            } else if (strcmp(key, "smtp_server") == 0) { 
                strcpy(smtp_server, json_object_get_string(val) );
            } else if (strcmp(key, "smtp_port") == 0) { 
                *smtp_port = json_object_get_int(val) ;
            } else if (strcmp(key, "pop_url") == 0) { 
                strcpy(pop_url, json_object_get_string(val) );
            } else if (strcmp(key, "imap_url") == 0) { 
                strcpy(imap_url, json_object_get_string(val) );
            } else if (strcmp(key, "user") == 0) { 
                strcpy(user, json_object_get_string(val) );
            } else if (strcmp(key, "passwd") == 0) { 
                strcpy(passwd, json_object_get_string(val) );
            } else if (strcmp(key, "to") == 0) { 
                strcpy(to, json_object_get_string(val) );
            } else if (strcmp(key, "from") == 0) { 
                strcpy(from, json_object_get_string(val) );
            }

    } // foreach

}


/**
 * printMailParam
 */
void printMailParam(struct MailParam p)
{
    printf("smtp_url: %s \n", p.smtp_url);
    printf("smtp_server: %s \n", p.smtp_server);
    printf("smtp_port: %d \n", p.smtp_port);
    printf("pop_url: %s \n", p.pop_url);
    printf("imap_url: %s \n", p.imap_url);
    printf("user: %s \n", p.user);
    printf("passwd: %s \n", p.passwd);
    printf("to: %s \n", p.to);
    printf("from: %s \n", p.from);
}

