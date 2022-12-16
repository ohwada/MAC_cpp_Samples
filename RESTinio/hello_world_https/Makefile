### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++14 
RESTINIO_FLAGS=`pkg-config --cflags --libs restinio`  
SSL_FLAGS=`pkg-config --cflags --libs openssl`  

TARGET=server
SRCS=hello_world_https.cpp


$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS) $(RESTINIO_FLAGS) $(SSL_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
