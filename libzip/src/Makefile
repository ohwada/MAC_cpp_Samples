### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
LIBS=-lzip
TARGET=show
SRCS=show_zip.c


$(TARGET):
	$(CC) $(SRCS) $(CFLAGS) $(LIBS) -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET) *.o 

