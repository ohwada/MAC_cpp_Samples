### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
HIREDIS_FLAGS=`pkg-config --cflags --libs hiredis`

TARGET1=example
SRCS1=example.c
TARGET2=show
SRCS2=show_values.c 


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) $(HIREDIS_FLAGS)  -o bin/$@ 


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) $(HIREDIS_FLAGS)  -o bin/$@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o

