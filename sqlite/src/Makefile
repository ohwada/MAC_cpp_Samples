### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
SQLITE_FLAGS=`pkg-config --cflags --libs sqlite3`

TARGET1=select
SRCS1=select.c
TARGET2=insert
SRCS2=insert.c
TARGET3=update
SRCS3=update.c
TARGET4=delete
SRCS4=delete.c
TARGET5=create
SRCS5=create_table.c
TARGET6=transaction
SRCS6=transaction.c


$(TARGET1): $(SRCS1)
	$(CC)  $<  $(CFLAGS) $(SQLITE_FLAGS) -o bin/$@
	cp test.db bin/test1.db


$(TARGET2): $(SRCS2)
	$(CC)  $<  $(CFLAGS) $(SQLITE_FLAGS) -o bin/$@
	cp test.db bin/test2.db


$(TARGET3): $(SRCS3)
	$(CC)  $<  $(CFLAGS) $(SQLITE_FLAGS) -o bin/$@
	cp test.db bin/test3.db


$(TARGET4): $(SRCS4)
	$(CC)  $<  $(CFLAGS) $(SQLITE_FLAGS) -o bin/$@
	cp test.db bin/test4.db


$(TARGET5): $(SRCS5)
	$(CC)  $<  $(CFLAGS) $(SQLITE_FLAGS) -o bin/$@
	cp test.db bin/test5.db


$(TARGET6): $(SRCS6)
	$(CC)  $<  $(CFLAGS) $(SQLITE_FLAGS) -o bin/$@
	cp test.db bin/test6.db


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o
