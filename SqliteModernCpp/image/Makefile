### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
MODERN_FLAGS=`pkg-config --cflags --libs sqlite_modern_cpp`
TARGET=image
SRCS=image.cpp 


$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CFLAGS)  $(MODERN_FLAGS) -o bin/$@
	cp movies.db bin
	cp -R images bin


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 
