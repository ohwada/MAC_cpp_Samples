### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
BOOST_FLAGS=`pkg-config --cflags  boost`

TARGET1=trim
SRCS1=trim.cpp
TARGET2=split
SRCS2=split.cpp
TARGET3=join
SRCS3=join.cpp
TARGET4=replace
SRCS4=string_replace_all.cpp
TARGET5=iends
SRCS5=iends_with.cpp
TARGET6=upper
SRCS6=to_upper.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET5): $(SRCS5)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET6): $(SRCS6)
	$(CXX) $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* out/*   *.o 
