### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
JSON_FLAGS=`pkg-config --cflags --libs json-c`

TARGET1=form
SRCS1=http_post_form_client.c
TARGET2=json
SRCS2=http_post_json_client.c
TARGET3=test_form
SRCS3=test_parse_response_post_form.c
TARGET4=test_json
SRCS4=test_parse_response_post_json.c

TARGET3=test_form
SRCS3=test_parse_response_post_form.c

$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) $(JSON_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS)  $(JSON_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $< $(CFLAGS)  $(JSON_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CC) $< $(CFLAGS)  $(JSON_FLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*  log/*   *.o 
