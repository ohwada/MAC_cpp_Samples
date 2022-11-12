### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
PCRE_FLAGS=`pkg-config --cflags --libs libpcre`

TARGET1=demo
SRCS1=pcredemo.c

TARGET2=pcre
SRCS2=pcre.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) $(PCRE_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) $(PCRE_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
