### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
 PNG_FLAGS=`pkg-config --cflags --libs libpng`
 
TARGET1=flag
SRCS1=românia_flag.c 
TARGET2=barcode
SRCS2=barcode.c 


$(TARGET1): $(SRCS1)
	$(CC) $(SRCS1) $(CFLAGS)  $(PNG_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $(SRCS2) $(CFLAGS)  $(PNG_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
