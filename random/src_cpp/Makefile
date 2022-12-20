### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
TCLAP_FLAGS=`pkg-config --cflags --libs tclap`

TARGET1=mkpasswd
SRCS1=mkpasswd.cpp
TARGET2=int
SRCS2=test_rand_int.cpp
TARGET3=real
SRCS3=test_rand_real.cpp
TARGET4=string
SRCS4=test_random_string.cpp
TARGET5=passwd
SRCS5=test_passwd.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $< $(CFLAGS)  $(TCLAP_FLAGS) -o bin/$@


$(TARGET2): $(SRCS2)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET3): $(SRCS3)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET4): $(SRCS4)
	$(CXX) $< $(CFLAGS) -o bin/$@


$(TARGET5): $(SRCS5)
	$(CXX) $< $(CFLAGS) -o bin/$@


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf  bin/* *.o 
