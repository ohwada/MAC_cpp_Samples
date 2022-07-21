### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
ARABICA_FLAGS=-I/usr/local/include/arabica -larabica  -lexpat
TARGET1=pyx
SRCS1=pyx.cpp
TARGET2=wrapper
SRCS2=wrapper.cpp SimpleHandler.cpp
TARGET3=writer
SRCS3=writer.cpp
TARGET4=xmlbase
SRCS4=xmlbase.cpp


$(TARGET1):
	$(CXX) $(SRCS1) $(ARABICA_FLAGS) $(CFLAGS) -o $@ 


$(TARGET2):
	$(CXX) $(SRCS2) $(ARABICA_FLAGS) $(CFLAGS) -o $@ 


$(TARGET3):
	$(CXX) $(SRCS3) $(ARABICA_FLAGS) $(CFLAGS) -o $@ 


$(TARGET4):
	$(CXX) $(SRCS4) $(ARABICA_FLAGS) $(CFLAGS) -o $@ 


%.o: %.c
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET) *.o
