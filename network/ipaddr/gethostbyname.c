/**
 * network sample
 * 2020-07-01 K.OHWADA
 */

// Get the IP Address from the host name
// using gethostbyname

// Note
// gethostbyname() functions is obsolete.  
// Applications should use getaddrinfo() instead.
// https://man7.org/linux/man-pages/man3/gethostbyname.3.html

// reference : https://paulschreiber.com/blog/2005/10/28/simple-gethostbyname-example/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>


/**
 * main
 */
int main(int argc, char *argv[]) 
{

    char *hostname = "google.com";

    if (argc == 2) {
        hostname = argv[1];
    } else {
        printf("Usage: %s [hostname] \n", argv[0]);
    }

    printf("hostname: %s \n", hostname);

    struct hostent *host1 = gethostbyname(hostname);

    if (host1 == NULL) {
       fprintf(stderr, "gethostbyname failed \n");
        herror("gethostbyname");
        return EXIT_FAILURE;
    }

    printf("genelic hostname: %s \n", host1->h_name);

// aliase list
unsigned int i=0;
while(1)
{
    char *aliase = host1 ->h_aliases[i];
    if(!aliase) {
        break;
    }

    printf("aliase: %s \n" , aliase );
     i++;
}

if( i==0 ){
printf("no aliases \n");
}


// address list
 i=0;
while(1)
{ 
    char *addr = host1 ->h_addr_list[i];
    if(!addr) {
        break;
    }

    char *str_addr = inet_ntoa( *( struct in_addr*)addr );
    printf( "addr %d : %s \n", i, str_addr);
    i++;
}

// first one adress
    char *ipaddr = inet_ntoa( *( struct in_addr*)host1 ->h_addr_list[0] );

    printf("ipaddr: %s \n", ipaddr);


    struct in_addr addr;
    addr.s_addr = inet_addr(ipaddr);
    int len = sizeof(addr.s_addr);

    struct hostent *host2 = gethostbyaddr( 
        (const char *)&addr.s_addr, len, AF_INET);

    if (host2 == NULL) {
       fprintf(stderr, "gethostbyaddr failed \n");
        herror("gethostbyaddr");
        return EXIT_FAILURE;
  }

    printf("reverse hostname: %s \n", host2->h_name);

    return EXIT_SUCCESS;
}


// hostname: google.com 
// genelic hostname: google.com 
// ipaddr: 172.217.175.14 
// reverse hostname: nrt20s18-in-f14.1e100.net 

