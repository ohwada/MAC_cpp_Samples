### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
MYSQL_FLAGS=`pkg-config --cflags --libs mysqlpp`

TARGET1=ssqls1
SRCS1=ssqls1.cpp printdata.cpp
TARGET2=ssqls2
SRCS2=ssqls2.cpp printdata.cpp
TARGET3=ssqls3
SRCS3=ssqls3.cpp printdata.cpp
 TARGET4=ssqls4
SRCS4=ssqls4.cpp printdata.cpp
 TARGET5=ssqls5
SRCS5=ssqls5.cpp printdata.cpp
 TARGET6=ssqls6
SRCS6=ssqls6.cpp printdata.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $(SRCS1) $(CFLAGS)  $(MYSQL_FLAGS)  -o bin/$@ 


$(TARGET2): $(SRCS2)
	$(CXX) $(SRCS2) $(CFLAGS)  $(MYSQL_FLAGS)  -o bin/$@ 


$(TARGET3): $(SRCS3)
	$(CXX) $(SRCS3) $(CFLAGS)  $(MYSQL_FLAGS)  -o bin/$@ 


$(TARGET4): $(SRCS4)
	$(CXX) $(SRCS4) $(CFLAGS)  $(MYSQL_FLAGS)  -o bin/$@ 


$(TARGET5): $(SRCS5)
	$(CXX) $(SRCS5) $(CFLAGS)  $(MYSQL_FLAGS)  -o bin/$@ 


$(TARGET6): $(SRCS6)
	$(CXX) $(SRCS6) $(CFLAGS)  $(MYSQL_FLAGS)  -o bin/$@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o

