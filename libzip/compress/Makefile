### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
ZIP_FLAGS=`pkg-config --cflags --libs libzip`


TARGET1=comp
SRCS1=comp.c
TARGET2=decomp
SRCS2=decomp.c


all: $(TARGET1) $(TARGET2)


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) $(ZIP_FLAGS) -o bin/$@
	cp -R test1 bin
	cp -R test2 bin


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) $(ZIP_FLAGS) -o bin/$@
	cp sample1.zip bin
	cp sample2.zip bin


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 

