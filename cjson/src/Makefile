### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
CJSON_FLAGS=-I/usr/local/include/cjson -lcjson
TARGET1=sample
SRCS1=sample.c
TARGET2=test
SRCS2=test.c


$(TARGET1):
	$(CC) $(SRCS1) $(CFLAGS) $(CJSON_FLAGS) -o $@


$(TARGET2):
	$(CC) $(SRCS2) $(CFLAGS) $(CJSON_FLAGS) -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2) *.o 

