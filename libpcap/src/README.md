libpcap: src
===============


## sample  
- lookupdev.c  
find device of network interface.  

- pcap_loop.c
get 20 packets and print the length of each packet

- sniffex.c  
 * Sniffer example of TCP/IP packet capture using libpcap.
callback function  
https://www.tcpdump.org/pcap.html  


Build and Run:
% make lookupdev
% bin/lookupdev
>  Device: en0


