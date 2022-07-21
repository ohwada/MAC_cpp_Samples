### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
ARABICA_FLAGS=-I/usr/local/include/arabica -larabica  -lexpat
TARGET=transcode
SRCS=transcode.cpp


$(TARGET):
	$(CXX) $(SRCS) $(ARABICA_FLAGS) $(CFLAGS) -o $@ 


%.o: %.c
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET) *.o
