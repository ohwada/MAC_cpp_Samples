### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
CRYPTOPP_FLAGS=`pkg-config --cflags --libs cryptopp`

TARGET1=3des
SRCS1=3des.cpp
TARGET2=user
SRCS2=user.cpp
TARGET3=file
SRCS3=file.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $(SRCS1) $(CFLAGS)  $(CRYPTOPP_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $(SRCS2) $(CFLAGS)  $(CRYPTOPP_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $(SRCS3) $(CFLAGS)  $(CRYPTOPP_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
