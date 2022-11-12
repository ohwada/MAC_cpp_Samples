/**
 * pcap_loopc
 * 2022-06-01 K.OHWADA
 */

// get 20 packets and print the length of each packet
// https://ben1jake.hatenablog.jp/entry/2017/08/31/005519

// FreeBSD jman: pcap_loop
// http://www.koganemaru.co.jp/cgi-bin/mroff.cgi?sect=3&cmd=&lc=1&subdir=man&dir=jpman-11.3.2%2Fman&subdir=man&man=pcap_loop

#include <stdio.h>
#include <pcap.h>


/**
 *  callback
 */
void callback(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    printf("packet length: %d\n", header->len);
}


/**
 *  main
 */
int main(int argc, char **argv) 
{
    char *dev, errbuf[PCAP_ERRBUF_SIZE];
    bpf_u_int32 net, mask;
    pcap_t *handle;
    struct bpf_program fp;

    char filter_exp[] = "";

    struct pcap_pkthdr header;
    const u_char *packet;

    dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
        return 2;
    }

    if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
        fprintf(stderr, "Can't get netmask for device %s: %s\n", dev, errbuf);
        return 2;
    }

    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return 2;
    }

    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return 2;
    }

    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return 2;
    }

    pcap_loop(handle, 20, callback, NULL);

    pcap_close(handle);

    return 0;
}


