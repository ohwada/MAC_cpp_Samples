### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
 FMT_FLAGS=`pkg-config --cflags --libs fmt`

TARGET=mini
SRCS=mini_lang.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(FMT_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 
