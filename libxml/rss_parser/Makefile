### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-I. -g -Wall -Werror
XML2_FLAGS=`xml2-config --cflags` 
XML2_LIBS=`xml2-config --libs`
TARGET=rss
SRCS= rss_parser.c


$(TARGET):
	$(CC) $(SRCS) $(CFLAGS) $(XML2_FLAGS) $(XML2_LIBS) -o $@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET) *.o
