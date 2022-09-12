### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++17
TARGET1=clamp
SRCS1=clamp.cpp
TARGET2=tuple
SRCS2=tuple.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $(CFLAGS) $< -o $@ 


$(TARGET2): $(SRCS2)
	$(CXX) $(CFLAGS) $< -o $@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2)  *.o

