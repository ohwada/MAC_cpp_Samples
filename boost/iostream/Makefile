### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
BOOST_FLAGS=`pkg-config --cflags --libs boost`

TARGET1=read
SRCS1=file_read.cpp
TARGET2=write
SRCS2=file_write.cpp
TARGET3=gzip
SRCS3=gzip.cpp
TARGET4=ungzip
SRCS4=ungzip.cpp


$(TARGET1): $(SRCS1)
	$(CXX)  $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX)  $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX)  $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@
	cp -R data bin


$(TARGET4): $(SRCS4)
	$(CXX)  $< $(CFLAGS)  $(BOOST_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
