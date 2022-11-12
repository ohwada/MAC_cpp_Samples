/**
 * lookupdev.c
 * 2022-06-01 K.OHWADA
 */

// find device of network interface.  

// reference:
// PROGRAMMING WITH PCAP
// https://www.tcpdump.org/pcap.html

// FreeBSD jman: pcap_lookupdev
// http://www.koganemaru.co.jp/cgi-bin/mroff.cgi?sect=3&cmd=&lc=1&subdir=man&dir=jpman-11.2.2%2Fman&subdir=man&man=pcap_lookupdev


#include <stdio.h>
#include <pcap.h>

int main(int argc, char *argv[])
{

	char *dev, errbuf[PCAP_ERRBUF_SIZE];
	
// warning: 'pcap_lookupdev' is deprecated: 
// use 'pcap_findalldevs' and use the first device
dev = pcap_lookupdev(errbuf);
	if (dev == NULL) {
		fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
		return(2);
	}
	printf("Device: %s\n", dev);
	return(0);
}

// Device: en0
