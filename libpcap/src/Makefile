### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
PCAP_FLAGS=`pkg-config --cflags --libs libpcap`

TARGET1=lookupdev
SRCS1=lookupdev.c
TARGET2=sniffex
SRCS2=sniffex.c
TARGET3=loop
SRCS3=pcap_loop.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS)  $(PCAP_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS)  $(PCAP_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $< $(CFLAGS)  $(PCAP_FLAGS) -o bin/$@


%.o: %.cp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
