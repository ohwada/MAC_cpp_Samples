### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
EV_FLAGS=`pkg-config --cflags --libs libev`


TARGET1=tailike
SRCS1=tailike.cpp 
TARGET2=timer
SRCS2=timer.cpp
TARGET3=server
SRCS3=echo-server.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $<  $(CFLAGS) $(EV_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $<  $(CFLAGS) $(EV_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $<  $(CFLAGS) $(EV_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
