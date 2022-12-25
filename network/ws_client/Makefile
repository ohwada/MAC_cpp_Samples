### 2022-10-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 

TARGET=client
SRCS=ws_client.c


$(TARGET): $(SRCS)
	$(CC) $< $(CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*  *.o 
