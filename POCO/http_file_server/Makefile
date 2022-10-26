### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
POCO_FLAGS= -lPocoNet -lPocoUtil  -lPocoFoundation -lPocoJSON


TARGET1=server
SRCS1=http_file_server.cpp
TARGET2=test
SRCS2=test_poco_mime.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
