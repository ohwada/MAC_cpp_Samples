### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
GTK_FLAGS=`pkg-config --cflags --libs gtk+-3.0`


TARGET1=gdk
SRCS1=gdk_pixbuf_new_from_file.c
TARGET2=cairo
SRCS2=cairo_image_surface_create_from_png.c
TARGET3=show
SRCS3=show_pixels.c


$(TARGET1): $(SRCS1)
	$(CC)  $<  $(CFLAGS) $(GTK_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC)   $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC)   $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
