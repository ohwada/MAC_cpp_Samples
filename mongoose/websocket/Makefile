### 2022-10-01 K.OHWADA

CC=gcc
CFLAGS=-Wall

TARGET1=server
SRCS1=websocket_server.c  mongoose.c  
TARGET2=client
SRCS2=websocket_client.c  mongoose.c  


$(TARGET1): $(SRCS1)
	$(CC) $(SRCS1) $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $(SRCS2) $(CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
