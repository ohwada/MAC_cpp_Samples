### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
POCO_FLAGS= -lPocoNet -lPocoUtil  -lPocoFoundation -lPocoJSON

TARGET1=get
SRCS1=http_get_form_server.cpp
TARGET2=post
SRCS2=http_post_form_server.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
