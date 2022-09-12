## 2022-06-01 K.OHWADA


CXX=g++
CFLAGS=-Wall -std=c++17

TARGET1=show
SRCS1=show_temp_directory_path.cpp
TARGET2=log
SRCS2=temporary_log.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*  *.o

