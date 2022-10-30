### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
POCO_FLAGS= -lPocoNet -lPocoUtil  -lPocoFoundation -lPocoJSON
 JSON_FLAGS=`pkg-config --cflags --libs jsoncpp`


TARGET1=client
SRCS1=test_readClientJsonFile.cpp
TARGET2=refresh
SRCS2=test_readRefreshTokenJsonFile.cpp
TARGET3=access
SRCS3=test_parseAccessTokenJson.cpp
TARGET4=mail
SRCS4=test_readMailParam.cpp

$(TARGET1):  $(SRCS1)
	$(CXX)  $<  $(CFLAGS) $(JSON_FLAGS)  -o bin/$@


$(TARGET2):  $(SRCS2)
	$(CXX)  $<  $(CFLAGS) $(JSON_FLAGS)  -o bin/$@


$(TARGET3):  $(SRCS3)
	$(CXX)  $<  $(CFLAGS) $(JSON_FLAGS)  -o bin/$@


$(TARGET4):  $(SRCS4)
	$(CXX)  $<  $(CFLAGS) $(JSON_FLAGS)  -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
