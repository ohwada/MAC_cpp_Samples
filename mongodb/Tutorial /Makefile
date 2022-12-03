### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall -Werror
MONGO_FLAGS=`pkg-config --cflags --libs libmongoc-1.0`


TARGET1=hello
SRCS1=hello_mongoc.c  
TARGET2=bson
SRCS2=bson.c  
TARGET3=bcon
SRCS3=bcon.c  
TARGET4=json
SRCS4=bson_json.c  
TARGET5=insert
SRCS5=insert.c  
TARGET6=find
SRCS6=find.c  
TARGET7=find_hello
SRCS7=find_hello.c  
TARGET8=update
SRCS8=update.c  
TARGET9=delete
SRCS9=delete.c  
TARGET10=count
SRCS10=count.c  
TARGET11=command
SRCS11=command.c  
TARGET12=pool
SRCS12=example-pool.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) $(MONGO_FLAGS)  -o bin/$@ 


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) $(MONGO_FLAGS)  -o bin/$@ 


$(TARGET3): $(SRCS3)
	$(CC) $< $(CFLAGS) $(MONGO_FLAGS)  -o bin/$@ 


$(TARGET4): $(SRCS4)
	$(CC) $< $(CFLAGS) $(MONGO_FLAGS)  -o bin/$@ 


$(TARGET5): $(SRCS5)
	$(CC) $< $(CFLAGS) $(MONGO_FLAGS)  -o bin/$@ 


$(TARGET6): $(SRCS6)
	$(CC) $< $(CFLAGS) $(MONGO_FLAGS)  -o bin/$@ 


$(TARGET7): $(SRCS7)
	$(CC) $< $(CFLAGS) $(MONGO_FLAGS)  -o bin/$@ 


$(TARGET8): $(SRCS8)
	$(CC) $< $(CFLAGS) $(MONGO_FLAGS)  -o bin/$@ 


$(TARGET9): $(SRCS9)
	$(CC) $< $(CFLAGS) $(MONGO_FLAGS)  -o bin/$@ 


$(TARGET10): $(SRCS10)
	$(CC) $< $(CFLAGS) $(MONGO_FLAGS)  -o bin/$@ 


$(TARGET11): $(SRCS11)
	$(CC) $< $(CFLAGS) $(MONGO_FLAGS)  -o bin/$@ 


$(TARGET12): $(SRCS12)
	$(CC) $< $(CFLAGS) $(MONGO_FLAGS)  -o bin/$@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o

