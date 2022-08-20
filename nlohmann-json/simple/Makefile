### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
TARGET=simple
SRCS=simple.cpp


$(TARGET):
	$(CXX) $(SRCS) $(CFLAGS) -o $@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET) *.o 
