### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
PARSON_SRCS=parson.c
CURL_LIBS=-lcurl
TARGET1=file
SRCS1=parse_file.c
TARGET2=url
SRCS2=parse_url.c


$(TARGET1):
	$(CC) $(SRCS1) $(PARSON_SRCS) $(CFLAGS) -o $@


$(TARGET2):
	$(CC) $(SRCS2) $(PARSON_SRCS) $(CFLAGS) $(CURL_LIBS) -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2) *.o
