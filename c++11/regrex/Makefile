### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11

TARGET1=match
SRCS1=regex_match.cpp
TARGET2=search
SRCS2=regex_search.cpp
TARGET3=replace
SRCS3=regex_replace.cpp



$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
