### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
POCO_FLAGS=-lPocoFoundation -lPocoJson 

TARGET=parse
SRCS=parse_json.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* out/*  *.o 
