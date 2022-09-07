### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror
TARGET=parse
SRCS=parse_url.cpp


$(TARGET): $(SRCS)
	$(CXX) $(CFLAGS) $< -o bin/$@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o

