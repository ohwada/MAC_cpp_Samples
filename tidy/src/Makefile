### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-I. -g -Wall -Werror
LIBS=-ltidy
TARGET1=sample
SRCS1=sample.c
TARGET2=tidy
SRCS2=tidy.c


$(TARGET1):
	$(CC) $(SRCS1) $(CFLAGS) $(LIBS) -o $@


$(TARGET2):
	$(CC) $(SRCS2) $(CFLAGS) $(LIBS) -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2) *.o *.dSYM
