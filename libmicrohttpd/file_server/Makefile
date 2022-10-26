### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
MHD_CFLAGS=`pkg-config --cflags --libs libmicrohttpd` 

TARGET=server
SRCS=file_server.c


$(TARGET): $(SRCS)
	$(CC) $< $(CFLAGS) $(MHD_CFLAGS) -o bin/$@



%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
