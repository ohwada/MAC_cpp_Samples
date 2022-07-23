### 2022-06-01 K.OHWADA
### reference : https://qiita.com/tobira-code/items/42803d1e203cbf44636f

CFLAGS=-Wall -Werror
INCS=test.h
OBJS=test.o
LIBS=#-lpthread -lm
TARGET=test

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf $(TARGET) *.o
