### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
GTK_FLAGS=`pkg-config --cflags --libs gtk+-3.0`


TARGET1=menu
SRCS1=menu.c
TARGET2=submenu
SRCS2=submenu.c
TARGET3=popupmenu
SRCS3=popupmenu.c
TARGET4=statusbar
SRCS4=statusbar.c
TARGET5=shortcutmenu
SRCS5=shortcutmenu.c
TARGET6=shortcutmenu2
SRCS6=shortcutmenu2.c
 TARGET7=toolbar
 SRCS7=toolbar.c
 TARGET8=toolbar2
 SRCS8=toolbar2.c

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


$(TARGET8): $(SRCS8)
	$(CC)   $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
