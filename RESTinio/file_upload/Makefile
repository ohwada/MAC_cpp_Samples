### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++14 
RESTINIO_FLAGS=`pkg-config --cflags --libs restinio`
CLARA_FLAGS=`pkg-config --cflags --libs clara`

TARGET=file
SRCS=file_upload.cpp


$(TARGET): $(SRCS)
	$(CXX)  $<  $(CFLAGS)  $(RESTINIO_FLAGS)  $(CLARA_FLAGS)  -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* upload/*  *.o 
