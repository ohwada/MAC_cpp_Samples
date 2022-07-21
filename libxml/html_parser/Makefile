### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-I. -g -Wall -Werror
XML2_FLAGS=`xml2-config --cflags` 
XML2_LIBS=`xml2-config --libs`
CURL_LIBS=-lcurl
TARGET1=parser1
SRCS1= html_parser1.cpp
TARGET2=parser2
SRCS2= html_parser2.cpp


$(TARGET1):
	$(CXX) $(SRCS1) $(CFLAGS) $(XML2_FLAGS) $(XML2_LIBS) -o $@ 


$(TARGET2):
	$(CXX) $(SRCS2) $(CFLAGS) $(XML2_FLAGS) $(XML2_LIBS) $(CURL_LIBS) -o $@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2) *.o
