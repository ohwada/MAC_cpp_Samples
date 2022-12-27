### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 

TARGET=join
SRCS=test_str_join.c


$(TARGET): $(SRCS)
	$(CC) $< $(CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
