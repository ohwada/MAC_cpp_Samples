## 2022-06-01 K.OHWADA


CC=gcc
CFLAGS=-Wall 
TURBO_FLAGS=`pkg-config --cflags --libs  libturbojpeg`
TARGET=example
SRCS=tjexample.c

$(TARGET): $(SRCS)
	$(CC) $< $(CFLAGS) $(TURBO_FLAGS)  -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*  *.o

