### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
LIBS=-ljansson
TARGET1=file
SRCS1=parse_file.c
TARGET2=simple
SRCS2=simple_parse.c


$(TARGET1): $(SRCS1)
	$(CC) $(CFLAGS) $(LIBS) $< -o $@


$(TARGET2): $(SRCS2)
	$(CC) $(CFLAGS) $(LIBS) $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2) *.o
