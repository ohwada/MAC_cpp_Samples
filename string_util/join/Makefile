### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11

TARGET1=join1
SRCS1=join1.cpp
TARGET2=join2
SRCS2=join2.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
