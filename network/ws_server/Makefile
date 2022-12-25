### 2022-10-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
SSL_FLAGS=`pkg-config --cflags --libs openssl`

TARGET=server
SRCS=ws_server.c


$(TARGET): $(SRCS)
	$(CC) $< $(CFLAGS)  $(SSL_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
