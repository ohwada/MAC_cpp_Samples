### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall

 CURL_FLAGS=`pkg-config --cflags --libs libcurl` 
 JSON_FLAGS=`pkg-config --cflags --libs json-c`

TARGET1=ssl
SRCS1=imap_ssl.c
TARGET2=list
SRCS2=imap_list.c
TARGET3=examine
SRCS3=imap_examine.c
TARGET4=fetch
SRCS4=imap_fetch.c


$(TARGET1): $(SRCS1)
	$(CC) $(SRCS1) $(CFLAGS)  $(CURL_FLAGS)  $(JSON_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $(SRCS2) $(CFLAGS)  $(CURL_FLAGS)  $(JSON_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $(SRCS3) $(CFLAGS)  $(CURL_FLAGS)  $(JSON_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CC) $(SRCS4) $(CFLAGS)  $(CURL_FLAGS)  $(JSON_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
