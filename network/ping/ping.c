/**
 * network sample
 * 2020-07-01 K.OHWADA
 */

// ping using ICMP
// gcc ping.c -o ping

// reference : https://www.geeksforgeeks.org/ping-in-c/

// Note:
// The strange case of ICMP Type 69 on Linux
// https://blog.benjojo.co.uk/post/linux-icmp-type-69

// compile as -o ping 
// run as sudo ./ping <hostname> 


#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <errno.h>
#include <time.h> 
#include <fcntl.h> 
#include <signal.h> 
#include <time.h>  
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/ip.h>
#include <netinet/ip_icmp.h> 
#include "ipaddr.h"


/**
 * macOS
 */
#ifdef __APPLE__ 
 #define SOL_IP IPPROTO_IP
struct icmphdr
{
  u_int8_t type;		/* message type */
  u_int8_t code;		/* type sub-code */
  u_int16_t checksum;
  union
  {
    struct
    {
      u_int16_t	id;
      u_int16_t	sequence;
    } echo;			/* echo datagram */
    u_int32_t	gateway;	/* gateway address */
    struct
    {
      u_int16_t	__unused;
      u_int16_t	mtu;
    } frag;			/* path mtu discovery */
  } un;
};
#endif 


// Define the Packet Constants 
// ping packet size 
#define PING_PKT_S 64 

// Automatic port number 
#define PORT_NO 0 

// Automatic port number 
#define PING_SLEEP_RATE 1000000

// Gives the timeout delay for receiving packets 
// in seconds 
#define RECV_TIMEOUT 1 

// Time To Live
#define TTL 64 

// Define the Ping Loop 
int pingloop = 1; 


// ping packet structure 
struct ping_pkt 
{ 
	struct icmphdr hdr; 
	char msg[PING_PKT_S - sizeof(struct icmphdr)]; 
}; 


// Calculating the Check Sum 
unsigned short checksum(void *b, int len) 
{ unsigned short *buf = b; 
	unsigned int sum=0; 
	unsigned short result; 

	for ( sum = 0; len > 1; len -= 2 ) 
		sum += *buf++; 
	if ( len == 1 ) 
		sum += *(unsigned char*)buf; 
	sum = (sum >> 16) + (sum & 0xFFFF); 
	sum += (sum >> 16); 
	result = ~sum; 
	return result; 
} 


// Interrupt handler 
void intHandler(int dummy) 
{ 
	pingloop = 0; 
} 


// make a ping request 
void send_ping(int ping_sockfd, struct sockaddr_in *ping_addr, 
				char *ping_dom, char *ping_ip, char *rev_host) 
{ 

	int ttl_val = TTL ; 
    int msg_count = 0;
    int i;
    int addr_len;
    int flag=1;
	int msg_received_count=0; 
	
	struct ping_pkt pckt; 
	struct sockaddr_in r_addr; 
	struct timespec time_start, time_end, tfs, tfe; 
	long double rtt_msec=0, total_msec=0; 
	struct timeval tv_out; 
	tv_out.tv_sec = RECV_TIMEOUT; 
	tv_out.tv_usec = 0; 

	clock_gettime(CLOCK_MONOTONIC, &tfs); 

	
	// set socket options at ip to TTL and value to 64, 
	// change to what you want by setting ttl_val 
	int ret1 = setsockopt(ping_sockfd, SOL_IP, IP_TTL, 
			&ttl_val, sizeof(ttl_val) ); 
	if (ret1 == 0) { 
	printf("\nSocket set to TTL: %d \n", TTL );
    } else {
        int save_err = errno;
		fprintf( stderr, "\nSetting socket options to TTL failed: %s \n", strerror(save_err) ); 
		return; 
	} 

	// setting timeout of recv setting 
	int ret2 = setsockopt( ping_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(tv_out) ); 
	if (ret2 == 0) { 
		printf("\nSocket set to TIMEOUT: %d \n", RECV_TIMEOUT ); 
    } else {
        int save_err = errno;
		fprintf( stderr, "\nSetting socket options to TIMEOUT failed: %s \n", strerror(save_err) ); 
		return; 
	} 

	// send icmp packet in an infinite loop 
	while(pingloop) 
	{ 
		// flag is whether packet was sent or not 
		flag=1; 
	
		//filling packet 
		bzero(&pckt, sizeof(pckt)); 
		
		pckt.hdr.type = ICMP_ECHO; 
		pckt.hdr.un.echo.id = getpid(); 
		
		for ( i = 0; i < sizeof(pckt.msg)-1; i++ ) 
			pckt.msg[i] = i+'0'; 
		
		pckt.msg[i] = 0; 
		pckt.hdr.un.echo.sequence = msg_count++; 
		pckt.hdr.checksum = checksum(&pckt, sizeof(pckt)); 


		usleep(PING_SLEEP_RATE); 

		//send packet 
		clock_gettime(CLOCK_MONOTONIC, &time_start); 

		ssize_t send_size = sendto(ping_sockfd, &pckt, sizeof(pckt), 0, 
		    (struct sockaddr*) ping_addr, 
			sizeof(*ping_addr) );
		if ( send_size <= 0 ) 
		{ 
			printf("\nPacket Sending Failed!\n"); 
			flag=0; 
		} 

		//receive packet 
		addr_len = sizeof(r_addr); 

		ssize_t recv_size = recvfrom(ping_sockfd, &pckt,
            sizeof(pckt), 0, 
			(struct sockaddr*)&r_addr, 
            (socklen_t *)&addr_len );
 
		if ( ( recv_size <= 0) && ( msg_count>1) ) 
		{ 
			printf("\nPacket receive failed!\n"); 
		} 
		else
		{ 
			clock_gettime(CLOCK_MONOTONIC, &time_end); 
			
			double timeElapsed = ((double)(time_end.tv_nsec - 
								time_start.tv_nsec))/1000000.0 ;
			rtt_msec = (time_end.tv_sec - time_start.tv_sec) * 1000.0 + timeElapsed; 
			
			// if packet was not sent, don't receive 
			if(flag) 
			{ 
		
				if( pckt.hdr.type ==69 ) 
				{ 
					printf("%d bytes from %s (h: %s) (%s) msg_seq=%d ttl=%d rtt = %Lf ms.\n", 
						PING_PKT_S, ping_dom, rev_host, 
						ping_ip, msg_count, 
						ttl_val, rtt_msec); 
			        if( pckt.hdr.code==0 ){ 
					        msg_received_count++; 
                    } else {
                        printf("warning: Packet received with ICMP type %d code %d\n", pckt.hdr.type, pckt.hdr.code);
                    }
				} else {
		            printf("Error: Packet received with ICMP type %d code %d\n", pckt.hdr.type, pckt.hdr.code); 
                }

			} 
		}	 
	} 
	clock_gettime(CLOCK_MONOTONIC, &tfe); 
	double timeElapsed = ((double)(tfe.tv_nsec - 
						tfs.tv_nsec))/1000000.0; 
	
	total_msec = (tfe.tv_sec-tfs.tv_sec)*1000.0+ timeElapsed ;
					
	float percent = ( (msg_count - msg_received_count) / msg_count) * 100.0;

	printf("\n===%s ping statistics===\n", ping_ip); 
	printf("\n%d packets sent, %d packets received, %f percent packet loss. Total time: %Lf ms.\n\n", 
		msg_count, msg_received_count, percent, total_msec); 
} 


/**
 * main
 */
int main(int argc, char *argv[]) 
{ 

    char *hostname;

	if(argc==2) {
        hostname = argv[1];
    } else { 
		printf("Usage: sudo %s <hostname> \n", argv[0]); 
		return EXIT_FAILURE;
	} 


	int sockfd; 

	char reverse_hostname[NI_MAXHOST]; 

    char ipaddress[100];

    char error[100];

	struct sockaddr_in addr_ping; 


// get ipaddress from hostname
    bool ret1 = get_ipaddress( hostname, NULL, (char *)ipaddress, (char*)error );
    if(!ret1){
		fprintf(stderr, "could not resolve: %s : %s \n", 
        hostname, (char *)error ); 
        return EXIT_FAILURE;
    }


    set_sockaddr( (char *)ipaddress, PORT_NO, &addr_ping );


// get reverse hostname 
    bool ret2 = get_hostname( (char *)ipaddress, (char *)reverse_hostname, NI_MAXHOST, (char *)error ) ;
    if(!ret2){
		fprintf(stderr, "could not resolve: %s : %s \n", 
        ipaddress, (char *)error ); 
        // return EXIT_FAILURE;
    }


	printf("\nReverse Lookup domain: %s \n", 
						reverse_hostname); 

	// create ICMP socket 
	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); 

	if( sockfd < 0 ) { 
            int save_err = errno;
		    fprintf( stderr, "socket error: %s \n", strerror(save_err) );
		    fprintf( stderr, "try 'sudo' \n" );  
		    return EXIT_FAILURE;
	} else {
		printf("Socket file descriptor %d received \n", sockfd); 
	}

	signal(SIGINT, intHandler);//catching interrupt 

	printf("\nTrying to connect to '%s' IP: %s \n", 
									hostname, ipaddress); 

	//send pings continuously 
	send_ping(sockfd, &addr_ping, hostname, 
	ipaddress, reverse_hostname); 
	

    return EXIT_SUCCESS;
} 



// Trying to connect to 'localhost' IP: 127.0.0.1
// 64 bytes from localhost (h: localhost) (127.0.0.1) msg_seq=1 ttl=64 rtt = 0.138000 ms.
// ===127.0.0.1 ping statistics===
// 20 packets sent, 20 packets received, 0.000000 percent packet loss. Total time: 19162.614000 ms

//Trying to connect to 'google.com' IP: 172.217.25.78 
// Error..Packet received with ICMP type 69 code 96

//PING www.google.com (172.217.175.100): 56 data bytes
//64 bytes from 172.217.175.100: icmp_seq=0 ttl=119 time=14.444 ms