### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
LIBS=-lxml2
TARGET=parse1
SRCS=parse1.c


$(TARGET):
	$(CC) $(SRCS) $(CFLAGS) $(LIBS) -o $@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET) *.o 
