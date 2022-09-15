## 2022-06-01 K.OHWADA


CXX=g++
CFLAGS=-Wall -std=c++11
BLAS_FLAGS=`pkg-config --cflags --libs openblas`
TARGET=matrix
SRCS=matrix.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS) $(BLAS_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*  *.o

