### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
GTK_FLAGS=`pkg-config --cflags --libs gtk+-3.0`
TARGET=texteditor
SRCS=texteditor.c


$(TARGET): $(SRCS)
	$(CC)   $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
