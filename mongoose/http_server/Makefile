### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall

TARGET1=hello
SRCS1=http_hello_server.c mongoose.c
TARGET2=index
SRCS2=http_index_server.c mongoose.c
TARGET3=file
SRCS3=http_file_server.c mongoose.c


$(TARGET1): $(SRCS1)
	$(CC) $(SRCS1) $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $(SRCS2) $(CFLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $(SRCS3) $(CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
