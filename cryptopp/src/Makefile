### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
CRYPTOPP_FLAGS=`pkg-config --cflags --libs cryptopp`

TARGET1=length
SRCS1=aes_length.cpp
TARGET2=cbc
SRCS2=aes_cbc.cpp
TARGET3=3des
SRCS3=3des.cpp
TARGET4=user
SRCS4=user.cpp
TARGET5=file
SRCS5=file.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(CRYPTOPP_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(CRYPTOPP_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS)  $(CRYPTOPP_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX) $< $(CFLAGS)  $(CRYPTOPP_FLAGS) -o bin/$@

$(TARGET5): $(SRCS5)
	$(CXX) $< $(CFLAGS)  $(CRYPTOPP_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
