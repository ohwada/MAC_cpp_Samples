### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
BZIP_FLAGS=`pkg-config --cflags --libs bzip2`

TARGET=test
SRCS=test.c


$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS)  $(BZIP_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
