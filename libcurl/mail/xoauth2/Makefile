### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
MHD_CFLAGS=`pkg-config --cflags --libs libmicrohttpd` 
CURL_CFLAGS=`pkg-config --cflags --libs libcurl` 
JSON_CFLAGS=`pkg-config --cflags --libs json-c` 


TARGET1=server
SRCS1=local_server.c
TARGET2=smtp
SRCS2=smtp_gmail_xoauth.c
TARGET3=access
SRCS3=request_access_token.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) $(MHD_CFLAGS) $(CURL_CFLAGS) $(JSON_CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) $(CURL_CFLAGS) $(JSON_CFLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $< $(CFLAGS) $(CURL_CFLAGS) $(JSON_CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* log/*  *.o 
