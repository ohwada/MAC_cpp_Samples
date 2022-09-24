### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
GIO_FLAGS=`pkg-config --cflags --libs gio-2.0` 

TARGET=server
SRCS=http_server.c


$(TARGET): $(SRCS)
	$(CC) $< $(CFLAGS) $(GIO_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
