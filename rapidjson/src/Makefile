### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
TARGET1=string
SRCS1=parse_string.cpp
TARGET2=file
SRCS2=parse_file.cpp


$(TARGET1):
	$(CXX) $(SRCS1) $(CFLAGS) -o $@


$(TARGET2):
	$(CXX) $(SRCS2) $(CFLAGS) -o $@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ 


clean:
	rm -rf $(TARGET1) $(TARGET2) *.o 

