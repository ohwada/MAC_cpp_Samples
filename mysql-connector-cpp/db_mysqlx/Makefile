### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
MYSQL_FLAGS=`pkg-config --cflags --libs mysqlcppconn`

TARGET=mysqlx
SRCS=mysqlx.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(MYSQL_FLAGS)  -o bin/$@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o

