### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
POCO_FLAGS= -lPocoNet -lPocoUtil  -lPocoFoundation -lPocoNetSSL
SSL_FLAGS=`pkg-config --cflags --libs openssl`

TARGET1=http
SRCS1=http_client.cpp
TARGET2=https
SRCS2=https_client.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) $(SSL_FLAGS) -o bin/$@



%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
