### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
TARGET=chrome
SRCS=chrome_open.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
