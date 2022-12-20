### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall

TARGET1=mkpasswd
SRCS1=mkpasswd.c
TARGET2=rand
SRCS2=test_rand.c
TARGET3=random
SRCS3=test_random.c
TARGET4=char
SRCS4=test_random_char.c
TARGET5=passwd
SRCS5=test_passwd.c
TARGET6=no_duplicate
SRCS6=gen_random_char_no_duplicate.c

$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $< $(CFLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CC) $< $(CFLAGS) -o bin/$@


$(TARGET5): $(SRCS5)
	$(CC) $< $(CFLAGS) -o bin/$@


$(TARGET6): $(SRCS6)
	$(CC) $< $(CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
