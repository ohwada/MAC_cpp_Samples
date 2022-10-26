### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall
JSON_FLAGS=`pkg-config --cflags --libs json-c`

TARGET1=form
SRCS1=http_post_form_client.c mongoose.c
TARGET2=json
SRCS2=http_post_json_client.c mongoose.c


$(TARGET1): $(SRCS1)
	$(CC) $(SRCS1) $(CFLAGS) $(JSON_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $(SRCS2) $(CFLAGS) $(JSON_FLAGS)  -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* log/*  *.o 
