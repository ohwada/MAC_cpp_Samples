### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
TARGET1=int
SRCS1=test_two_dem_int_array.c
TARGET2=char
SRCS2=test_two_dem_char_array.c

$(TARGET1): $(SRCS1)
	$(CC) $(CFLAGS) $< -o $@ 


$(TARGET2): $(SRCS2)
	$(CC) $(CFLAGS) $< -o $@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1)  $(TARGET2) *.o

