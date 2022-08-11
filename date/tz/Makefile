### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++11

DATE_PATH=../date
DATE_FLAGS=-I$(DATE_PATH)/include/ -I$(DATE_PATH)/include/date/
CURL_FLAGS=`pkg-config --cflags --libs libcurl` 
TARGET=meeting 
SRCS=meeting_time.cpp $(DATE_PATH)/src/tz.cpp 


all: $(TARGET) setup


$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CFLAGS) $(DATE_FLAGS) $(CURL_FLAGS)  -o bin/$@ 


%.o: %.c
	$(CXX) $(CFLAGS) -c -o $@ $<


setup:
	cp -R tzdata ~/Downloads/


clean:
	rm -rf bin/$(TARGET) *.o

