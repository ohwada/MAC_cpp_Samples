### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 

TARGET1=hello
SRCS1=http_hello_server.c
TARGET2=index
SRCS2=http_index_server.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
