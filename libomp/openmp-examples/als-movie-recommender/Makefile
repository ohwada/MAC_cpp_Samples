### 2022-06-01 K.OHWADA

CXX = g++
CFLAGS=-I. -g -Wall -Werror
OMP_FLAGS=-Xpreprocessor -fopenmp -lomp
EIGN_FLAGS=-I/usr/local/include/eigen3
TARGET=als_list
SRCS=main.cpp

$(TARGET):
	$(CXX) $(SRCS) $(OMP_FLAGS) $(EIGN_FLAGS) -o $(TARGET)

%.o: %.cpp $(INCS)
	$(CXX) $(CFLAGS) -c -o $@ $<



clean:
	rm -rf $(TARGET) *.o
