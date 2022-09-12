### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++17
TARGET1=recursive
SRCS1=recursive_directory_iterator.cpp



$(TARGET1): $(SRCS1)
	$(CXX) $(CFLAGS) $< -o bin/$@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o

