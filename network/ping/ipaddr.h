/**
 * network sample
 * 2020-07-01 K.OHWADA
 */

// Get the IP Address from the host name
// using getaddrinfo


#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


// prototype
bool get_ipaddress(char *hostname, char *service, char *ipaddress, char*error);
bool get_hostname(char *ipaddress, char *hostname, socklen_t  hostlen, char *error ) ;
void set_sockaddr(char *ip_addr, int port, struct sockaddr_in *addr);


/**
 * get_ipaddress
* solve IP address with DNS lookup
 */
bool get_ipaddress(char *hostname, char *service, char *ipaddress, char*error)
{

    struct addrinfo hints, *info;
  
    memset(&hints, 0, sizeof(hints));

    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int err = getaddrinfo(hostname, service, &hints, &info);
    if (err != 0) {
        strcpy( error, gai_strerror(err) );
        return false;
    }

    struct in_addr addr;

    addr.s_addr = ((struct sockaddr_in *)(info->ai_addr))->sin_addr.s_addr;

    strcpy( ipaddress, inet_ntoa(addr) );

    freeaddrinfo(info);

     return true;
}


/**
 * get_hostname
* resolve IP address with forward DNS lookup
 */

/**
 * get_hostname
* resolve hostname with reverse DNS lookup
 */
bool get_hostname(char *ipaddress, char *hostname, socklen_t  hostlen, char *error ) 
{ 

	struct sockaddr_in addr;	 
	addr.sin_family = AF_INET; 
	addr.sin_addr.s_addr = inet_addr(ipaddress); 
	socklen_t addr_len = sizeof(struct sockaddr_in); 

	int err = getnameinfo( (struct sockaddr *)&addr, addr_len, hostname, hostlen, NULL, 0, NI_NAMEREQD );

	if (err != 0) { 
        strcpy( error, gai_strerror(err) );
		return false; 
	} 

	return true; 
} 


/**
 * set_sockaddr
 */
void set_sockaddr(char *ip_addr, int port, struct sockaddr_in *addr) 
{ 

	(* addr).sin_family = AF_INET; 
	(* addr).sin_addr.s_addr = inet_addr( ip_addr ); 
	(* addr).sin_port = htons (port); 
	
} 
