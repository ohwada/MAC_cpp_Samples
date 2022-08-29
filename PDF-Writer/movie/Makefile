### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++11
PDF_FLAGS=`pkg-config --cflags --libs pdfwriter`
TARGET=movie
SRCS=movie.cpp
 

$(TARGET): $(SRCS)
	$(CXX) $< $(CFLAGS) $(PDF_FLAGS) -o $@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET) *.o

