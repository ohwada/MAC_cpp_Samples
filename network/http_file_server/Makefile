### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 

TARGET1=server
SRCS1=http_file_server.c
TARGET2=test
SRCS2=test_request_parser.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* log/*  *.o 
