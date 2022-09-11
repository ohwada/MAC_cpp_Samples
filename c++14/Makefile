### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++14
TARGET1=constexpr
SRCS1=constexpr.cpp
TARGET2=lambda
SRCS2=lambda.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $(CFLAGS) $< -o $@ 


$(TARGET2): $(SRCS2)
	$(CXX) $(CFLAGS) $< -o $@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2)  *.o

