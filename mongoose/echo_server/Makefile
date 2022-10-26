### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall

TARGET=server
SRCS=tcp_echo_server.c mongoose.c


$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
