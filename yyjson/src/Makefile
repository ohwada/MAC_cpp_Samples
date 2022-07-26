### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
TARGET=file
SRCS=parse_file.c parson.c


$(TARGET):
	$(CC) $(SRCS) $(CFLAGS) -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET) *.o
