### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++11
MODERN_FLAGS=`pkg-config --cflags --libs sqlite_modern_cpp`
TARGET=insert
SRCS=insert.cpp 


$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CFLAGS)  $(MODERN_FLAGS) -o bin/$@
	cp movies.db bin


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/$(TARGET) *.o 
