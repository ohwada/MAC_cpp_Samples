### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++14
CATCH2_FLAGS=`pkg-config --cflags --libs  catch2-with-main`

TARGET=test
SRCS=010-TestCase.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(CATCH2_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* log/* *.o 
