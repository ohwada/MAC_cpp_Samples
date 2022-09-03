### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
JSON_FLAGS=`pkg-config --cflags --libs json-c`

TARGET1=string
SRCS1=parse_string.c
TARGET2=file
SRCS2=parse_file.c
TARGET3=array
SRCS3=parse_array.c
TARGET4=mail
SRCS4=parse_mail.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) $(JSON_FLAGS)  -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) $(JSON_FLAGS)  -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $< $(CFLAGS) $(JSON_FLAGS)  -o bin/$@


$(TARGET4): $(SRCS4)
	$(CC) $< $(CFLAGS) $(JSON_FLAGS)  -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o
