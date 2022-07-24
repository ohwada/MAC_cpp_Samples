### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror
LIBS=-lxml2
CURL_LIBS=-lcurl
TARGET1=file
SRCS1= html_parser_file.cpp
TARGET2=url
SRCS2= html_parser_url.cpp


$(TARGET1):
	$(CXX) $(SRCS1) $(CFLAGS) $(LIBS) -o $@ 


$(TARGET2):
	$(CXX) $(SRCS2) $(CFLAGS) $(LIBS) $(CURL_LIBS) -o $@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2) *.o 
