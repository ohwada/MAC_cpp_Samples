### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 

TARGET1=order
SRCS1=byte_order.c
TARGET2=swap
SRCS2=byte_swap.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*    *.o 
