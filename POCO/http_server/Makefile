### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
POCO_FLAGS= -lPocoNet -lPocoUtil  -lPocoFoundation -lPocoJSON


TARGET1=hello
SRCS1=http_hello_server.cpp
TARGET2=index
SRCS2=http_index_server.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* log/*  *.o 
