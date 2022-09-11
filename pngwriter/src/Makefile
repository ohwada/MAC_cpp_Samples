### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
WRITER_FLAGS=`pkg-config --cflags --libs pngwriter`

TARGET1=sin
SRCS1=sin_wave.cpp
TARGET2=pngtest
SRCS2=pngtest.cc
TARGET3=flag
SRCS3= românia_flag.cpp
TARGET4=captcha
SRCS4=captcha.cpp
TARGET5=barcode
SRCS5=barcode.cpp


$(TARGET1): $(SRCS1)
	$(CXX)  $< $(CFLAGS)  $(WRITER_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX)  $< $(CFLAGS)  $(WRITER_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX)  $< $(CFLAGS)  $(WRITER_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX)  $< $(CFLAGS)  $(WRITER_FLAGS) -o bin/$@


$(TARGET5): $(SRCS5)
	$(CXX)  $< $(CFLAGS)  $(WRITER_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
