### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
PDF_FLAGS=`pkg-config --cflags --libs pdfwriter`
TARGET=simple
SRCS=simple.cpp


$(TARGET):
	$(CXX) $(SRCS) $(CFLAGS)  $(PDF_FLAGS) -o $@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET) *.o 
