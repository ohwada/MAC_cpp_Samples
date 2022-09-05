### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
GTK_FLAGS=`pkg-config --cflags --libs gtkmm-3.0` 

TARGET1=window
SRCS1=window.cpp
TARGET2=mouse
SRCS2=mouse_event.cpp
TARGET3=box_button
SRCS3=box_button.cpp


$(TARGET1):  $(SRCS1)
	$(CXX)  $<  $(CFLAGS) $(GTK_FLAGS) -o bin/$@


$(TARGET2):  $(SRCS2)
	$(CXX)  $<  $(CFLAGS) $(GTK_FLAGS) -o bin/$@


$(TARGET3):  $(SRCS3)
	$(CXX)  $<  $(CFLAGS) $(GTK_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
