### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall

 PNG_FLAGS=`pkg-config --cflags --libs libpng`
 GTK_FLAGS=`pkg-config --cflags --libs gtk+-2.0`


TARGET1=copy
SRCS1=copy.c 
TARGET2=gray
SRCS2=gray.c
TARGET3=write
SRCS3=pixel_write.c 
TARGET4=gtk
SRCS4=gtk.c 


$(TARGET1): $(SRCS1)
	$(CC) $(SRCS1) $(CFLAGS)  $(PNG_FLAGS) -o bin/$@
	cp -R images bin


$(TARGET2): $(SRCS2)
	$(CC) $(SRCS2) $(CFLAGS)  $(PNG_FLAGS) -o bin/$@
	cp -R images bin


$(TARGET3): $(SRCS3)
	$(CC) $(SRCS3) $(CFLAGS)  $(PNG_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CC) $(SRCS4) $(CFLAGS)  $(PNG_FLAGS) $(GTK_FLAGS) -o bin/$@



%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
