### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
SOCI_FLAGS=`pkg-config --cflags --libs soci_sqlite`


TARGET=sqlite
SRCS=soci_sqlite.cpp


$(TARGET): $(SRCS)
	$(CXX)  $< $(CFLAGS)  $(SOCI_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
