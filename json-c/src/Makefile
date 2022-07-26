### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
JSON_FLAGS= -I/usr/local/include/json-c -ljson-c
TARGET1=string
SRCS1=parse_string.c
TARGET2=file
SRCS2=parse_file.c
TARGET3=mail
SRCS3=parse_mail.c


$(TARGET1): $(SRCS1)
	$(CC) $(CFLAGS) $(JSON_FLAGS) $< -o $@


$(TARGET2): $(SRCS2)
	$(CC) $(CFLAGS) $(JSON_FLAGS) $< -o $@


$(TARGET3): $(SRCS3)
	$(CC) $(CFLAGS) $(JSON_FLAGS) $< -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2)  $(TARGET3) *.o
