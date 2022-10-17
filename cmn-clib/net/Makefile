### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall

CLIB_FLAGS=`pkg-config --cflags --libs cmn-clib` 

TARGET1=test
SRCS1=test_CmnNet.c
TARGET2=server
SRCS2=server.c
TARGET3=client
SRCS3=client.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) $(CLIB_FLAGS)-o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS)  $(CLIB_FLAGS) $ -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $< $(CFLAGS)  $(CLIB_FLAGS) $ -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
