### 2022-06-01 K.OHWADA

CC=gcc
CFLAGS=-Wall 
JSON_CFLAGS=`pkg-config --cflags --libs json-c` 


TARGET1=server
SRCS1=test_server_client.c
TARGET2=mail
SRCS2=test_mail_json.c
TARGET3=client
SRCS3=test_read_client_credentials.c
TARGET4=refresh
SRCS4=test_readRefreshTokenJsonFile.c
TARGET4=access
SRCS4=test_parseAccessTokenJson.c


$(TARGET1): $(SRCS1)
	$(CC) $< $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CC) $< $(CFLAGS) $(JSON_CFLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CC) $< $(CFLAGS) $(JSON_CFLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CC) $< $(CFLAGS) $(JSON_CFLAGS) -o bin/$@


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* log/*  *.o 
