### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall

 CURL_FLAGS=`pkg-config --cflags --libs libcurl` 

TARGET1=client
SRCS1=https_client.c
TARGET2=file
SRCS2=https_client_file.c
TARGET2=memory
SRCS2=https_client_memory.c


$(TARGET1): $(SRCS1)
	$(CC) $(SRCS1) $(CFLAGS)  $(CURL_FLAGS)  $ -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $(SRCS2) $(CFLAGS)  $(CURL_FLAGS)  $ -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $(SRCS2) $(CFLAGS)  $(CURL_FLAGS)  $ -o bin/$@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
