### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
LIBS=-lxml2
TARGET=rss
SRCS=rss_parser.c


$(TARGET):
	$(CC) $(SRCS) $(CFLAGS) $(LIBS) -o $@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET) *.o 
