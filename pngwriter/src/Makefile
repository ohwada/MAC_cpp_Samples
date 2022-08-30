### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11 -I.
PNG_FLAGS=`pkg-config --cflags --libs libpng`
FREETYPE_FLAGS=`pkg-config --cflags --libs freetype2` 
TARGET1=sin
SRCS1=sin_wave.cpp pngwriter.cc
TARGET2=pngtest
SRCS2=pngtest.cc pngwriter.cc
TARGET3=flag
SRCS3= românia_flag.cpp pngwriter.cc
TARGET4=captcha
SRCS4=captcha.cpp pngwriter.cc
TARGET5=barcode
SRCS5=barcode.cpp pngwriter.cc


$(TARGET1): $(SRCS1)
	$(CXX) $(SRCS1) $(CFLAGS)  $(PNG_FLAGS)  $(FREETYPE_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $(SRCS2) $(CFLAGS)  $(PNG_FLAGS)  $(FREETYPE_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $(SRCS3) $(CFLAGS)  $(PNG_FLAGS)  $(FREETYPE_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX) $(SRCS4) $(CFLAGS)  $(PNG_FLAGS)  $(FREETYPE_FLAGS) -o bin/$@


$(TARGET5): $(SRCS5)
	$(CXX) $(SRCS5) $(CFLAGS)  $(PNG_FLAGS)  $(FREETYPE_FLAGS) -o bin/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
