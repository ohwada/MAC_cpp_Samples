### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++17
GTK_FLAGS=`pkg-config --cflags --libs gtkmm-4.0` 

TARGET=image
SRCS=main.cc  myarea.cc


$(TARGET):  $(SRCS)
	$(CXX)  $(SRCS)  $(CFLAGS) $(GTK_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
