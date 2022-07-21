### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
ARABICA_FLAGS=-I/usr/local/include/arabica -larabica  -lexpat
TARGET1=dom2pyx
SRCS1=dom2pyx.cpp
TARGET2=writer
SRCS2=DOMWriter.cpp

$(TARGET1):
	$(CXX) $(SRCS1) $(ARABICA_FLAGS) $(CFLAGS) -o $@ 


$(TARGET2):
	$(CXX) $(SRCS2) $(ARABICA_FLAGS) $(CFLAGS) -o $@ 



%.o: %.c
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET) *.o
