### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
CRYPTOPP_FLAGS=`pkg-config --cflags --libs cryptopp`

TARGET1=enc
SRCS1=enc_dec.cpp
TARGET2=sign
SRCS2=sign.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $(SRCS1) $(CFLAGS)  $(CRYPTOPP_FLAGS) -o bin/$@
	cp sample.txt bin


$(TARGET2): $(SRCS2)
	$(CXX) $(SRCS2) $(CFLAGS)  $(CRYPTOPP_FLAGS) -o bin/$@
	cp sample.txt bin


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
