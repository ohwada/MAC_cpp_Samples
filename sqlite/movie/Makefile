### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
SQLITE_FLAGS=`pkg-config --cflags --libs sqlite3`

TARGET=movie
SRCS=movie.c


$(TARGET): $(SRCS)
	$(CC)  $<  $(CFLAGS) $(SQLITE_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o
