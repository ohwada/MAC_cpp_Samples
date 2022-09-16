## 2022-06-01 K.OHWADA


CXX=g++
CFLAGS=-Wall -std=c++17
CAIRO_FLAGS=`pkg-config --cflags --libs  cairomm-1.16`

TARGET1=surface
SRCS1=imagesurface.cpp
TARGET2=color
SRCS2=bgcolor.cpp
TARGET3=polygon
SRCS3=polygon.cpp

$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS) $(CAIRO_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) $(CAIRO_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS) $(CAIRO_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/*  *.o

