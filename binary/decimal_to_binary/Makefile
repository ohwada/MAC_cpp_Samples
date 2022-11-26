### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall

TARGET=test
SRCS=test_decimal_to_binary.c


$(TARGET): $(SRCS)
	$(CC)  $<  $(CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o
