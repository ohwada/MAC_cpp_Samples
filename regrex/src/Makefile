### 2022-06-01 K.OHWADA

CXX=g++
CFLAGS=-Wall -Werror -std=c++11
TARGET1=match
SRCS1=regex_match.cpp
TARGET2=results
SRCS2=match_results.cpp

$(TARGET1): $(SRCS1)
	$(CXX) $(CFLAGS) $< -o $@ 


$(TARGET2): $(SRCS2)
	$(CXX) $(CFLAGS) $< -o $@ 


%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2) *.o

