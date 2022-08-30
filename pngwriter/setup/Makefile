### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall  -shared  -fpic  -std=c++11 -Isrc
PNG_FLAGS=`pkg-config --cflags --libs libpng`
FREETYPE_FLAGS=`pkg-config --cflags --libs freetype2` 
TARGET=libpngwriter.a
SRCS=src/pngwriter.cc


$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CFLAGS)  $(PNG_FLAGS)  $(FREETYPE_FLAGS) -o lib/$@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf lib/$(TARGET)  *.o 
