### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++14
 FMT_FLAGS=`pkg-config --cflags --libs fmt`

TARGET1=print
SRCS1=print.cpp
TARGET2=string
SRCS2=string.cpp
TARGET3=chrono
SRCS3=chrono.cpp


$(TARGET1):  $(SRCS1)
	$(CXX)  $<  $(CFLAGS)  $(FMT_FLAGS) -o bin/$@


$(TARGET2):  $(SRCS2)
	$(CXX)  $<  $(CFLAGS) $(FMT_FLAGS) -o bin/$@


$(TARGET3):  $(SRCS3)
	$(CXX)  $<  $(CFLAGS) $(FMT_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
