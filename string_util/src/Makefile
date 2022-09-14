### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
TARGET1=split
SRCS1=test_split.cpp
TARGET2=trim
SRCS2=test_trim.cpp
TARGET3=toupper
SRCS3=toupper.cpp


$(TARGET1): $(SRCS1)
	$(CXX)  $< $(CFLAGS) -o bin/$@ 


$(TARGET2): $(SRCS2)
	$(CXX)  $< $(CFLAGS) -o bin/$@ 


$(TARGET3): $(SRCS3)
	$(CXX)  $< $(CFLAGS) -o bin/$@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o

