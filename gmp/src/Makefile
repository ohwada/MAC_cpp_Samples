### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror -lgmp 
TARGET1=random
SRCS1=random.c
TARGET2=prime
SRCS2=prime.c


$(TARGET1): $(SRCS1)
	$(CC) $(CFLAGS) $< -o $@ 


$(TARGET2): $(SRCS2)
	$(CC) $(CFLAGS) $< -o $@ 


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2)  *.o

