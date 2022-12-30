### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11

TARGET1=test
SRCS1=test.cpp base64.cpp
TARGET2=image
SRCS2=test_image_file.cpp base64.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $(SRCS1) $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $(SRCS2) $(CFLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
