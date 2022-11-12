### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
PCRE_FLAGS=`pkg-config --cflags --libs libpcre2-8`

TARGET1=demo
SRCS1=pcre2demo.c
TARGET2=pcre2
SRCS2=pcre2.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) $(PCRE_FLAGS) -o bin/$@


$(TARGET2):  $(SRCS2)
	$(CC) $< $(CFLAGS) $(PCRE_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
