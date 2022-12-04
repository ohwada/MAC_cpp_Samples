### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
SQLITE_FLAGS=`pkg-config --cflags --libs sqlite3`

TARGET1=create
SRCS1=create_image_table.c
TARGET2=insert
SRCS2=insert_image.c
TARGET3=select
SRCS3=select_image.c


$(TARGET1): $(SRCS1)
	$(CC)  $<  $(CFLAGS) $(SQLITE_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC)  $<  $(CFLAGS) $(SQLITE_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC)  $<  $(CFLAGS) $(SQLITE_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* out/* *.o
