### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
BOOST_FLAGS=`pkg-config --cflags  boost`
TARGET1=ip_address
SRCS1=ip_address.cpp
TARGET2=resolver
SRCS2=resolver.cpp
TARGET3=version
SRCS3=version.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $(SRCS1) $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $(SRCS2) $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $(SRCS3) $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
