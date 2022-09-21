### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++14
TARGET1=pointer
SRCS1=pointer.cpp
TARGET2=function
SRCS2=function.cpp
TARGET3=messenger
SRCS3=messenger.cpp
TARGET4=interface
SRCS4=interface.cpp
TARGET5=generic
SRCS5=generic.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET5): $(SRCS5)
	$(CXX) $< $(CFLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
