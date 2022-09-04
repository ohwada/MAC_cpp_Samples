### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
GTK_FLAGS=`pkg-config --cflags --libs gtk+-3.0`

TARGET1=line
SRCS1=line.c
TARGET2=point
SRCS2=point.c
TARGET3=shape
SRCS3=shape.c
TARGET4=color
SRCS4=color.c
TARGET5=image
SRCS5=image.c


$(TARGET1): $(SRCS1)
	$(CC)   $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC)   $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC)   $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CC)   $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


$(TARGET5): $(SRCS5)
	$(CC)   $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
