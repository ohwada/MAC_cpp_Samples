### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
PASER_FLAGS=`pkg-config --cflags --libs nodejs_http_parser`

TARGET=test
SRCS=test.c


$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) $(PASER_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
