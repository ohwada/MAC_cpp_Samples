### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++11
MODERN_FLAGS=`pkg-config --cflags --libs sqlite_modern_cpp`
TARGET=select
SRCS=select.cpp 


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(MODERN_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 
