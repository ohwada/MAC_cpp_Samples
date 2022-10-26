### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
POCO_FLAGS= -lPocoNet -lPocoUtil  -lPocoFoundation -lPocoJSON -lPocoNetSSL
SSL_FLAGS=`pkg-config --cflags --libs openssl` 

TARGET=client
SRCS=https_client.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) $(SSL_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
