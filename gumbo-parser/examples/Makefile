### 2022-06-01 K.OHWADA

CC=gcc
CXX=g++
CFLAGS=-I. -g -Wall -Werror
LIBS=-lgumbo
TARGET1=get_title
SRCS1=get_title.c
TARGET2=find_links
SRCS2=find_links.cc


$(TARGET1):
	$(CC) $(SRCS1) $(CFLAGS) $(LIBS) -o $@ 


$(TARGET2):
	$(CXX) $(SRCS2) $(CFLAGS) $(LIBS) -o $@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf $(TARGET1) $(TARGET2) *.o
