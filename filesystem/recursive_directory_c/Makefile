### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
TARGET=size
SRCS=recursive_file_size.c


$(TARGET): $(SRCS)
	$(CC) $< $(CFLAGS)  -o bin/$@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o

