### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
GTK_FLAGS=`pkg-config --cflags --libs gtk+-3.0`


TARGET1=message
SRCS1=messagedialog.c
TARGET2=font
SRCS2=fontdialog.c
TARGET3=font2
SRCS3=fontdialog2.c
TARGET4=file
SRCS4=filedialog.c
TARGET5=file2
SRCS5=filedialog2.c
TARGET6=color
SRCS6=colordialog.c
 TARGET7=color2
 SRCS7=colordialog2.c


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


$(TARGET6): $(SRCS6)
	$(CC)   $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


$(TARGET7): $(SRCS7)
	$(CC)   $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
