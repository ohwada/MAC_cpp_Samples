### 2022-06-01 K.OHWADA

CXX=/usr/local/bin/g++-12
CFLAGS=-Wall  -std=c++20 

TARGET1=contains
SRCS1=map_contains.cpp
TARGET2=starts_with
SRCS2=string_starts_with.cpp
TARGET3=format
SRCS3=format.cpp
TARGET4=numbers
SRCS4=numbers.cpp


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
	rm -rf bin/* *.o

