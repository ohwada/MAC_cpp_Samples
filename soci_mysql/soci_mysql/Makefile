### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++14
SOCI_FLAGS=`pkg-config --cflags --libs soci_mysql`


TARGET=mysql
SRCS=soci_mysql.cpp


$(TARGET): $(SRCS)
	$(CXX)  $< $(CFLAGS)  $(SOCI_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
