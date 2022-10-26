### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
SSL_FLAGS=`pkg-config --cflags --libs openssl` -DMG_ENABLE_OPENSSL=1

TARGET1=http
SRCS1=http_client.c mongoose.c
TARGET2=https
SRCS2=https_client.c mongoose.c


$(TARGET1): $(SRCS1)
	$(CC) $(SRCS1) $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $(SRCS2) $(CFLAGS) $(SSL_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* log/*  *.o 
