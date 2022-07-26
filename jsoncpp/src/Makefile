### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -std=c++11
LIBS=-ljsoncpp
TARGET1=string
SRCS1=parse_string.cpp
TARGET2=file
SRCS2=parse_file.cpp
TARGET3=person
SRCS3=parse_parson.cpp
TARGET4=to_json
SRCS4=to_json.cpp


$(TARGET1): $(SRCS1)
	$(CXX) $(CFLAGS) $(LIBS) $< -o $@


$(TARGET2): $(SRCS2)
	$(CXX) $(CFLAGS) $(LIBS) $< -o $@


$(TARGET3): $(SRCS3)
	$(CXX) $(CFLAGS) $(LIBS) $< -o $@


$(TARGET4): $(SRCS4)
	$(CXX) $(CFLAGS) $(LIBS) $< -o $@


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2)  $(TARGET3) $(TARGET4) *.o
