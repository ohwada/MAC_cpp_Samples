### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++17


ZIPLIB_FLAGS=`pkg-config --cflags --libs ziplib`
TARGET1=comp
SRCS1=comp.cpp
TARGET2=decomp
SRCS2=decomp.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $(SRCS1) $(CFLAGS) $(ZIPLIB_FLAGS) -o bin/$@ 
	cp -R test bin


$(TARGET2): $(SRCS2)
	$(CXX) $(SRCS2) $(CFLAGS) $(ZIPLIB_FLAGS) -o bin/$@ 
	mkdir bin/temp
	cp passwd.zip bin


%.o: %.c
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o

