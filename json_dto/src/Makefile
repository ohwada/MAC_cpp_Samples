### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++14
JSON_FLAGS=`pkg-config --cflags  json_dto`

TARGET=tutorial1
SRCS=tutorial1.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(JSON_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* log/* *.o 
