### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall

TARGET1=test
SRCS1=test_bin_hex.c
TARGET2=image
SRCS2=test_image_file.c


$(TARGET1): $(SRCS1)
	$(CC)  $<  $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC)  $<  $(CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* out/* *.o
