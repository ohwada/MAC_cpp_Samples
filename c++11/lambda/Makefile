### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11

TARGET1=hello
SRCS1=hello.cpp
TARGET2=assign
SRCS2=assign.cpp
TARGET3=argument
SRCS3=argument.cpp
TARGET4=return
SRCS4=return_value.cpp
TARGET5=capture
SRCS5=capture.cpp
TARGET6=rewrite
SRCS6=rewrite.cpp


$(TARGET1): $(SRCS2)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET5): $(SRCS5)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET6): $(SRCS6)
	$(CXX) $< $(CFLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* *.o 
