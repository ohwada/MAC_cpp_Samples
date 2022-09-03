### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
LIBS= -lexpat
TARGET=movie
SRCS=movie.c


$(TARGET):
	$(CC) $(SRCS) $(CFLAGS) $(LIBS) -o bin/$@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
