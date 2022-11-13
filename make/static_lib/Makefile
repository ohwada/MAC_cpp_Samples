### make static shared libraly
### 2022-06-01 K.OHWADA

CC=gcc
CCFLAGS=-Wall -c
LDFLAGS=-Wall -L./lib -lhello
LBTOOL_FLAG=-c -static
TARGET=hello
MAIN_SRCS=main.c
LIB=lib/libhello.a
OBJ=objs/hello.o
SRC=sub/hello.c


$(TARGET): $(MAIN_SRCS) $(LIB)
	$(CC) $(MAIN_SRCS) $(LDFLAGS) -o bin/$@


$(LIB): $(OBJ)
	libtool $(OBJ) $(LBTOOL_FLAG) -o $@


$(OBJ): $(SRC)
	$(CC) $< $(CCFLAGS) -o $@


clean:
	rm -rf bin/* objs/* lib/*
