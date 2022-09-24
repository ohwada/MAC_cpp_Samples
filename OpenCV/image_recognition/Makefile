### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
OCV_FLAGS=`pkg-config --cflags --libs opencv4` 

TARGET1=cat
SRCS1=cat_face _detect.cpp
TARGET2=qrcode
SRCS2=qrcode.cpp
TARGET3=blob
SRCS3=detect_blob.cpp


$(TARGET1):  $(SRCS1)
	$(CXX)  $<  $(CFLAGS) $(OCV_FLAGS) -o bin/$@
	cp -R images bin


$(TARGET2):  $(SRCS2)
	$(CXX)  $<  $(CFLAGS) $(OCV_FLAGS) -o bin/$@
	cp -R images bin


$(TARGET3):  $(SRCS3)
	$(CXX)  $<  $(CFLAGS) $(OCV_FLAGS) -o bin/$@
	cp -R images bin


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
