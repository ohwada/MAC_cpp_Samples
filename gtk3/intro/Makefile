### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
GTK_FLAGS=`pkg-config --cflags --libs gtk+-3.0`
TARGET1=hello
SRCS1=hello.c
TARGET2=window
SRCS2=window.c


$(TARGET1): $(SRCS1)
	$(CC)   $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC)   $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@



%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
