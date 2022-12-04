### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
SSL_FLAGS=`pkg-config --cflags --libs openssl`

TARGET1=sha256
SRCS1=sha256.c
TARGET2=sha1
SRCS2=sha1.c
TARGET3=md5
SRCS3=md5.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS)  $(SSL_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS)  $(SSL_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $< $(CFLAGS)  $(SSL_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*    *.o 
