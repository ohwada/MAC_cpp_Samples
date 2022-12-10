### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
BOOST_FLAGS=`pkg-config --cflags  boost`

TARGET1=uuid
SRCS1=uuid.cpp
TARGET2=sha1
SRCS2=sha1.cpp
TARGET3=md5
SRCS3=md5.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* out/*   *.o 
