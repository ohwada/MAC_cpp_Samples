### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
GTK_FLAGS=`pkg-config --cflags --libs gtk+-3.0`

TARGET1=button
SRCS1=button.c
TARGET2=checkbutton
SRCS2=checkbutton.c
TARGET3=radiobutton
SRCS3=radiobutton.c
TARGET4=togglebutton
SRCS4=togglebutton.c
TARGET5=scale
SRCS5=scale.c
TARGET6= listbox
SRCS6= listbox.c
TARGET7=combo
SRCS7=comboboxtext.c


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
	$(CC) $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


$(TARGET7): $(SRCS7)
	$(CC) $< $(CFLAGS) $(GTK_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
