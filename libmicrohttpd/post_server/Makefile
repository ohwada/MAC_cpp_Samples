### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
MHD_CFLAGS=`pkg-config --cflags --libs libmicrohttpd` 

TARGET1=simple
SRCS1=simple_post_server.c
TARGET2=session
SRCS2=post_session_server.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) $(MHD_CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) $(MHD_CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
