### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
ANSI_FLAGS=-ansi -pedantic
TARGET1=variable
SRCS1=variable.c  
TARGET2=ansi_variable


$(TARGET1): $(SRCS1)
	$(CC) $(CFLAGS) $< -o $@ 


$(TARGET2): $(SRCS1)
	$(CC) $(CFLAGS) $(ANSI_FLAGS) $< -o $@ 


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2)  *.o

