### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
MHD_CFLAGS=`pkg-config --cflags --libs libmicrohttpd` 
TLS_CFLAGS=`pkg-config --cflags --libs gnutls`

TARGET1=http
SRCS1=http_server.c
TARGET2=https
SRCS2=https_server.c

$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) $(MHD_CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) $(MHD_CFLAGS) $(TLS_CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
