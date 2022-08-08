 /**
 * parse_url.c
 * 2022-06-01 K.OHWADA
 */

// gcc parse_url.c


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>

const int BUFSIZE = 100;
 /**
 * struct url_parts
 */
struct url_parts
{
    char protocol[BUFSIZE]; 
    char domain[BUFSIZE]; 
    int port; 
    char path[BUFSIZE]; 
    char query[BUFSIZE]; 
    char fragment[BUFSIZE]; 
    bool valid;
};


 /**
 * parse_url
 */
 struct url_parts parse_url(const char* uri)
{
    const char NUL = '\0';

   // std::regex rx(R"(^(\w+):\/\/([\w.-]+)(:(\d+))?([\w\/\.]+)?(\?([\w=&]*)(#?(\w+))?)?$)");

    const char PATTERN[] = "([a-z]+)://([a-z.]+)(:([0-9]+))?(/[a-z./]+)?(.*)";

    const int MATCH_SIZE = 10;
    regmatch_t match[MATCH_SIZE];

char buf[MATCH_SIZE][BUFSIZE];

for(int i=0; i<MATCH_SIZE; i++)
{
        for(int j=0; j<BUFSIZE; j++){
            buf[i][j] = NUL;
        } // for j       
} // for i

    regex_t buffer;


    struct url_parts p1;
    p1.valid = false;

    if ( regcomp(&buffer, PATTERN, REG_EXTENDED) != 0 )
    {
        printf("regcomp failed \n");
        return p1;
    }

   int ret = regexec(&buffer, uri, MATCH_SIZE, match, 0);

    regfree(&buffer);

    struct url_parts p2;
    p2.valid = false;

    if(ret != 0){
        printf("unmatch \n");
        return p2;
    }

   for ( int i = 0; i < MATCH_SIZE; i++ )
    {
        int startIndex = match[i].rm_so; 
        int endIndex = match[i].rm_eo; 
        if ( startIndex == -1 || endIndex == -1 )
        {
            continue;
        }

        // printf("index [start, end] = %d, %d\n", startIndex, endIndex);
        strncpy(buf[i], uri + startIndex, endIndex - startIndex);
        // printf("%d: %s \n", i, buf[i]);
    } // for

// buf[6]: ?lite=true#ui 

char text[BUFSIZE];
char query[BUFSIZE];
char  fragment[BUFSIZE];

    for(int i=0; i<BUFSIZE; i++){
        text[i] = NUL;
        query[i] = NUL;
        fragment[i] = NUL;
    }

const char QUESTION = '?';
const char SQUARE = '#';

// parse with QUESTION('?') and  SQUARE('#')  
// instead of regular expressions

    strcpy(text, buf[6]);
    int len = strlen(text);
    if(len>0) {
        char ch = text[0] ;
        if(ch == QUESTION) {
            char *p = strchr(text, SQUARE);
            if(p == NULL) {
                strcpy( query, &text[1]);
            }else{
                strcpy( fragment, &p[1]);
                int len1 = len - strlen(fragment) -2;
                strncpy(query, text +1,  len1);
            } // if p
        } else if(ch == SQUARE) {
                strcpy( fragment, &text[1]);
        } // if ch
    } // if len


    // printf("query: %s \n",  query);
    // printf("fragment: %s \n",  fragment);

    struct url_parts parts;

    strcpy(parts.protocol, buf[1]);
    strcpy(parts.domain, buf[2]);
    parts.port = atoi(buf[4]);
    strcpy(parts.path, buf[5]);
   strcpy(parts.query, query);
   strcpy(parts.fragment, fragment);
    parts.valid = true;

    return parts;
}


 /**
 *  print_param
 */
void print_param( struct url_parts p)
{
    int port = p.port;
    printf("protocol: %s \n", p.protocol);
    printf("domain : %s \n", p.domain );
    if(port>0){
        printf("port : %d \n", port );
    }
    printf("path : %s \n", p.path );
    printf("query : %s \n", p.query );
    printf("fragment : %s \n", p.fragment );
}


 /**
 * main
 */
int main()
{
const char* URL1 =  (char*)"https://example.com";
const char* URL2 =  (char* )"https://example.com:80/en/index.html?lite=true#abc";
const char* URL3 =  (char* )"https://example.com:80/en/index.html?lite=true";
const char* URL4 =  (char* )"https://example.com:80/en/index.html#abc";

// case 1
 printf("%s \n", URL1);

   struct url_parts  p1 = parse_url(URL1);
 print_param(p1);


// case 2
 printf("\n %s \n", URL2);

      struct url_parts p2 = parse_url(URL2);
    print_param(p2);

// case 3
 printf("\n %s \n", URL3);

      struct url_parts p3 = parse_url(URL3);
    print_param(p3);

// case 4
 printf("\n %s \n", URL4);

      struct url_parts p4 = parse_url(URL4);
    print_param(p4);

    return 0;
}


// https://example.com:80/en/index.html?lite=true#abc 
// protocol: https 
// domain : example.com 
// port : 80 
// path : /en/index.html 
// query : lite=true 
//fragment : abc 

