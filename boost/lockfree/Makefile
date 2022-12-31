### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
BOOST_FLAGS=`pkg-config --cflags boost`

TARGET1=queue
SRCS1=lockfree_queue.cpp
TARGET2=stack
SRCS2=lockfree_stack.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) $(BOOST_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
