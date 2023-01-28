### 2022-10-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
LOG_FLAGS=`pkg-config --cflags --libs  spdlog`

TARGET1=basic
SRCS1=basic.cpp
TARGET2=stdout
SRCS2=stdout_logger.cpp
TARGET3=file
SRCS3=file_logger.cpp
TARGET4=rotating
SRCS4=rotating_files.cpp
TARGET5=daily
SRCS5=daily_files.cpp
TARGET6=backtrace
SRCS6=  backtrace.cpp
TARGET7=example
SRCS7=example.cpp



$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) $(LOG_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) $(LOG_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS) $(LOG_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX) $< $(CFLAGS) $(LOG_FLAGS) -o bin/$@


$(TARGET5): $(SRCS5)
	$(CXX) $< $(CFLAGS) $(LOG_FLAGS) -o bin/$@


$(TARGET6): $(SRCS6)
	$(CXX) $< $(CFLAGS) $(LOG_FLAGS) -o bin/$@


$(TARGET7): $(SRCS7)
	$(CXX) $< $(CFLAGS) $(LOG_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/* logs/*  *.o 
