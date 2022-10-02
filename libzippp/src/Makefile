### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
ZIP_FLAGS=`pkg-config --cflags --libs libzippp`

TARGET1=add
SRCS1=add_data.cpp
TARGET2=remove
SRCS2=remove_data.cpp
TARGET3=progress
SRCS3=progress.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(ZIP_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS)  $(ZIP_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS)  $(ZIP_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
