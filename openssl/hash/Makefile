### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
SSL_FLAGS=`pkg-config --cflags --libs openssl`

TARGET1=sha1
SRCS1=sha1.c
TARGET2=sha256
SRCS2=sha256.c
TARGET3=sha512
SRCS3=sha512.c
TARGET4=md5
SRCS4=md5.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS)  $(SSL_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS)  $(SSL_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $< $(CFLAGS)  $(SSL_FLAGS) -o bin/$@


 $(TARGET4): $(SRCS4)
	$(CC) $< $(CFLAGS)  $(SSL_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*    *.o 
