### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
FACIL_FLAGS=`pkg-config --cflags --libs facil`

TARGET1=hello
SRCS1=http-hello.c
TARGET2=echo
SRCS2=raw-echo.c
TARGET3=index
SRCS3=http_index.c

$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) $(FACIL_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) $(FACIL_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $< $(CFLAGS) $(FACIL_FLAGS) -o bin/$@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
