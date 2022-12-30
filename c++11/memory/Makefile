### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11

TARGET1=shared
SRCS1=shared_ptr.cpp
TARGET2=unique
SRCS2=unique_ptr.cpp
TARGET3=weak
SRCS3=weak_ptr.cpp
TARGET4=shared_from_this
SRCS4= shared_from_this.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX) $< $(CFLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
