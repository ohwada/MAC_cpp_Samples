### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
TARGET1=string
SRCS1=parse_string.c
TARGET2=simple
SRCS2=simple.c


$(TARGET1): $(SRCS1)
	$(CC) $(CFLAGS) $< -o $@


$(TARGET2): $(SRCS2)
	$(CC) $(CFLAGS) $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2)  *.o
