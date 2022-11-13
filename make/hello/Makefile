### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall

TARGET=hello
SRCS=main.c sub/hello.c


$(TARGET): $(SRCS)
	$(CC)  $(SRCS) $(CFLAG) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 
