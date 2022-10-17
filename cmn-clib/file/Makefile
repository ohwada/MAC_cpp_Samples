### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall

 CLIB_FLAGS=`pkg-config --cflags --libs cmn-clib` 

TARGET1=read
SRCS1=file_read.c
TARGET2=write
SRCS2=file_write.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS)  $(CLIB_FLAGS)  $ -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS)  $(CLIB_FLAGS)  $ -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  test/*  *.o 
