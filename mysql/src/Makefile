### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
MYSQL_FLAGS=`pkg-config --cflags --libs mysqlclient`
TARGET=mysql
SRCS=mysql.c  



$(TARGET): $(SRCS)
	$(CC) $< $(CFLAGS) $(MYSQL_FLAGS)  -o bin/$@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o

