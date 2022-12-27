### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11

TARGET1=replace
SRCS1=str_replace.cpp
TARGET2=all
SRCS2=str_replace_all.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
