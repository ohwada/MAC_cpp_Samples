/**
 * parse_mail.c
 * 2020-03-01 K.OHWADA
 */

// parse mail json file
// reference : https://github.com/koara-local/json-test/blob/master/json.cpp

#include <stdio.h>
#include <string.h>
#include <json.h>


/**
 * struct MailParam
 */
struct MailParam {
char* server;
int port;
char* user;
char* passwd;
char* to;
char* from;
};


// prototype
struct MailParam getMailParam(char* filepath);
void parseMailJson(struct json_object* const obj, 
char* server, int* port, char* user, char* passwd, char* to, char* from) ;
void printMailParam(struct MailParam p);


/**
 * getMailParam
 */
struct MailParam getMailParam(char* filepath)
{

    static struct MailParam p;

    char* server = (char *)malloc(100);
    char* user = (char *)malloc(100);
    char* passwd = (char *)malloc(100);
    char* to = (char *)malloc(100);
    char* from = (char *)malloc(100);
    int port;

    struct json_object *jobj_from_file = json_object_from_file(filepath);

    if (json_object_is_type(jobj_from_file, json_type_null)) {
        printf( "json_object_from_file faild: %s \n", filepath );
        return p;
    }

    parseMailJson(jobj_from_file, 
server, &port, user, passwd, to, from );

    p.server = server;
    p.port = port;
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
char* server, int* port, char* user, char* passwd, char* to, char* from) 
{

    json_object_object_foreach(obj, key, val) {

            if (strcmp(key, "server") == 0) { 
                strcpy(server, json_object_get_string(val) );
            } else if (strcmp(key, "port") == 0) { 
                *port = json_object_get_int(val);
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
    printf("server: %s \n", p.server);
    printf("port: %d \n", p.port);
    printf("user: %s \n", p.user);
    printf("passwd: %s \n", p.passwd);
    printf("to: %s \n", p.to);
    printf("from: %s \n", p.from);
}

/**
 * main
 */
int main(int argc, char **argv) 
{
    char* file = (char *)"jsons/mail.json";

    if(argc == 2){
        file = argv[1];
    } else {
        printf("Usage: %s <jsonFile> \n", argv[0]);
    }

        printf("file: %s \n", file);

    struct MailParam p = getMailParam(file);

    printMailParam(p);


    return 0;
}


// server: ubuntu 
// port: 25 
// user: taro 
// passwd: 123456789 
// to: taro@ubuntu 
// from: hoge@example.org 

