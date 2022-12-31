### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
BOOST_FLAGS=`pkg-config --cflags boost`

TARGET1=scoped
SRCS1=scoped_ptr.cpp
TARGET2=shared
SRCS2=shared_ptr.cpp
TARGET3=weak
SRCS3=weak_ptr.cpp
TARGET4=enable
SRCS4=enable_shared_from_this.cpp



$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) $(BOOST_FLAGS) -o bin/$@


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
