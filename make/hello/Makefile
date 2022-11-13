### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
DIR_GUARD=@mkdir -p $(@D)

TARGET=bin/hello
SRCS=main.c sub/hello.c


$(TARGET): $(SRCS)
	$(DIR_GUARD)
	$(CC)  $(SRCS) $(CFLAG) -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 
