### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
MYSQL_FLAGS=`pkg-config --cflags --libs mysqlpp`

TARGET=resetdb
SRCS=resetdb.cpp printdata.cpp


$(TARGET): $(SRCS)
	$(CXX)  $(SRCS)  $(CFLAGS)  $(MYSQL_FLAGS)  -o bin/$@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o

