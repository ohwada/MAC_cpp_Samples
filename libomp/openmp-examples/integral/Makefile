### 2022-06-01 K.OHWADA

CXX = g++
CFLAGS=-I. -g -Wall -Werror
OMP_FLAGS=-Xpreprocessor -fopenmp -lomp
TARGET=integral
SRCS=main.cpp

$(TARGET):
	$(CXX) $(SRCS) $(OMP_FLAGS) -o $(TARGET)

%.o: %.cpp $(INCS)
	$(CXX) $(CFLAGS) -c -o $@ $<



clean:
	rm -rf $(TARGET) *.o
