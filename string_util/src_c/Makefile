### 2022-06-01 K.OHWADA

CXX=gcc
CFLAGS=-Wall 
TARGET1=split
SRCS1=test_split.c
TARGET2=trim
SRCS2=test_trim.c
TARGET3=toupper
SRCS3=toupper.c


$(TARGET1): $(SRCS1)
	$(CC)  $< $(CFLAGS) -o bin/$@ 


$(TARGET2): $(SRCS2)
	$(CC)  $< $(CFLAGS) -o bin/$@ 


$(TARGET3): $(SRCS3)
	$(CC)  $< $(CFLAGS) -o bin/$@ 


%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -rf bin/*  *.o

