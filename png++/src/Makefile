### 2022-06-01 K.OHWADA

CC=g++
CFLAGS=-Wall -std=c++11

 PNG_FLAGS=`pkg-config --cflags --libs pngpp`
 GTK_FLAGS=`pkg-config --cflags --libs gtk+-2.0`

TARGET1=copy
SRCS1=copy.cpp 
TARGET2=gray
SRCS2=gray.cpp 
TARGET3=write
SRCS3=pixel_write.cpp 
TARGET4=gtk
SRCS4=gtk.cpp 


$(TARGET1): $(SRCS1)
	$(CXX) $(SRCS1) $(CFLAGS)  $(PNG_FLAGS) -o bin/$@
	cp -R images bin


$(TARGET2): $(SRCS2)
	$(CXX) $(SRCS2) $(CFLAGS)  $(PNG_FLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $(SRCS3) $(CFLAGS)  $(PNG_FLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX) $(SRCS4) $(CFLAGS)  $(PNG_FLAGS) $(GTK_FLAGS) -o bin/$@



%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o 
