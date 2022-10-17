### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall

CLIB_FLAGS=`pkg-config --cflags --libs cmn-clib` 

TARGET=client
SRCS=http_client.c


$(TARGET): $(SRCS)
	$(CC) $< $(CFLAGS) $(CLIB_FLAGS)-o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* log/*  *.o 
