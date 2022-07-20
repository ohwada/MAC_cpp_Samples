### 2022-06-01 K.OHWADA

CXX = g++
CFLAGS=-I. -g -Wall -Werror -std=c++11
OMP_FLAGS=-Xpreprocessor -fopenmp -lomp
TARGET=linkedlist
SRCS=main.cpp

$(TARGET):
	$(CXX) $(SRCS) $(CFLAGS) $(OMP_FLAGS) -o $(TARGET)

%.o: %.cpp $(INCS)
	$(CXX) $(CFLAGS) -c -o $@ $<



clean:
	rm -rf $(TARGET) *.o
