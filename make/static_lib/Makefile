### make static shared libraly
### 2022-06-01 K.OHWADA

CC=gcc
CCFLAGS=-Wall -c
LDFLAGS=-Wall -L./lib -lhello
LBTOOL_FLAG=-c -static
DIR_GUARD=@mkdir -p $(@D)

TARGET=bin/hello
MAIN_SRCS=main.c
LIB=lib/libhello.a
OBJ=objs/hello.o
SRC=sub/hello.c


$(TARGET): $(MAIN_SRCS) $(LIB)
	$(DIR_GUARD)
	$(CC) $(MAIN_SRCS) $(LDFLAGS) -o $@


$(LIB): $(OBJ)
	$(DIR_GUARD)
	libtool $(OBJ) $(LBTOOL_FLAG) -o $@


$(OBJ): $(SRC)
	$(DIR_GUARD)
	$(CC) $< $(CCFLAGS) -o $@


clean:
	rm -rf bin/* objs/* lib/*
