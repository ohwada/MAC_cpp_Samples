### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
JSON_FLAGS=`pkg-config --cflags --libs json-c`

TARGET=movie
SRCS=movie.c


$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(JSON_FLAGS) $< -o bin/$@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o
