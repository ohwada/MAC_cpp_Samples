### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 

 HARU_FLAGS=`pkg-config --cflags --libs libharu`
TARGET=movie
SRCS=movie.c


$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS)  $(HARU_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
