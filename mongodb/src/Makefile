### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
MONGO_FLAGS=`pkg-config --cflags --libs libmongoc-1.0`


TARGET=show
SRCS=show_db_test.c


$(TARGET): $(SRCS)
	$(CC) $< $(CFLAGS) $(MONGO_FLAGS)  -o bin/$@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o

