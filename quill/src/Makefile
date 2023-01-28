### 2022-10-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++17
LOG_FLAGS=`pkg-config --cflags --libs  quill`

TARGET1=basic
SRCS1=basic.cpp
TARGET2=file
SRCS2=example_logging_to_file.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) $(LOG_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) $(LOG_FLAGS) -o bin/$@

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* logs/*  *.o 
