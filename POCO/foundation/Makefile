### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
POCO_FLAGS=-lPocoFoundation 

TARGET1=now
SRCS1=now.cpp
TARGET2=path
SRCS2=path.cpp
TARGET3=file
SRCS3=file_read_write.cpp
TARGET4=log
SRCS4=logger.cpp

$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX) $< $(CFLAGS)  $(POCO_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* out/*  *.o 
