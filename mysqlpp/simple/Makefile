### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
MYSQL_FLAGS=`pkg-config --cflags --libs mysqlpp`

TARGET1=simple1
SRCS1=simple1.cpp printdata.cpp
TARGET2=simple2
SRCS2=simple2.cpp printdata.cpp
TARGET3=simple3
SRCS3=simple3.cpp printdata.cpp


$(TARGET1): $(SRCS1)
	$(CXX)  $(SRCS1)  $(CFLAGS)  $(MYSQL_FLAGS)  -o bin/$@ 


$(TARGET2): $(SRCS2)
	$(CXX)  $(SRCS2)  $(CFLAGS)  $(MYSQL_FLAGS)  -o bin/$@ 


$(TARGET3): $(SRCS3)
	$(CXX)  $(SRCS3)  $(CFLAGS)  $(MYSQL_FLAGS)  -o bin/$@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o

