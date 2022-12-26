### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
CW_FLAGS=`pkg-config --cflags --libs cwebsocket`

TARGET1=server
SRCS1=websocket-server.c
TARGET2=client
SRCS2=websocket-client.c


$(TARGET1): $(SRCS1)
	$(CC) $(SRCS1) $(CFLAGS) $(CW_FLAGS) -o bin/$@ 


$(TARGET2): $(SRCS2)
	$(CC) $(SRCS2) $(CFLAGS) $(CW_FLAGS) -o bin/$@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o

