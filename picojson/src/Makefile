### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
TARGET=file
SRCS=parse_file.cc


$(TARGET):
	$(CXX) $(SRCS) $(CFLAGS) -o $@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ 


clean:
	rm -rf $(TARGET) *.o 

