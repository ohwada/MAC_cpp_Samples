### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
GTK_FLAGS=`pkg-config --cflags --libs gtkmm-3.0` 

TARGET1=socket
SRCS1=socket.cc
TARGET2=plug
SRCS2=plug.cc


$(TARGET1):  $(SRCS1)
	$(CXX)  $<  $(CFLAGS) $(GTK_FLAGS) -o bin/$@


$(TARGET2):  $(SRCS2)
	$(CXX)  $<  $(CFLAGS) $(GTK_FLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
