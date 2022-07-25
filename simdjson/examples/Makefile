### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
LIBS=-lsimdjson
TARGET1=quickstart
SRCS1=quickstart.cpp
TARGET2=quickstart2
SRCS2=quickstart2.cpp


$(TARGET1):
	$(CXX) $(SRCS1) $(CFLAGS) $(LIBS) -o $@


$(TARGET2):
	$(CXX) $(SRCS2) $(CFLAGS) $(LIBS) -o $@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ 


clean:
	rm -rf $(TARGET1) $(TARGET2) *.o 

