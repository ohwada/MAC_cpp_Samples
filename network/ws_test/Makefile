### 2022-10-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
SSL_FLAGS=`pkg-config --cflags --libs openssl`

TARGET1=key
SRCS1=test_gen_accept_key.c
TARGET2=frame
SRCS2=test_ws_frame_parser.c
TARGET3=request
SRCS3=test_ws_request_parser.ctest_gen_accept_key.c
TARGET4=server
SRCS4=test_ws_server_frame_builder.c
TARGET5=client
SRCS5=test_ws_client_frame_builder.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) $(SSL_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $< $(CFLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CC) $< $(CFLAGS) -o bin/$@


$(TARGET5): $(SRCS5)
	$(CC) $< $(CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
