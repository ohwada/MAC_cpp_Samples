### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 

 HARU_FLAGS=`pkg-config --cflags --libs libharu`
TARGET=image
SRCS=image.c

$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS)  $(HARU_FLAGS) -o bin/$@
	cp -R images bin


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
