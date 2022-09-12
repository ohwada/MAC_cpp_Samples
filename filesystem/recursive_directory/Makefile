### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++17

TARGET1=show
SRCS1=recursive_show_file.cpp
TARGET2=size
SRCS2=recursive_file_size.cpp
TARGET3=last_write
SRCS3=recursive_last_write_time.cpp
TARGET4=find
SRCS4=recursive_find_file.cpp


$(TARGET1): $(SRCS1)
	$(CXX)  $< $(CFLAGS) -o bin/$@ 


$(TARGET2): $(SRCS2)
	$(CXX)  $< $(CFLAGS) -o bin/$@ 


$(TARGET3): $(SRCS3)
	$(CXX)  $< $(CFLAGS) -o bin/$@ 


$(TARGET4): $(SRCS4)
	$(CXX)  $< $(CFLAGS) -o bin/$@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/$(TARGET) *.o

