### make dynamic shared libraly
### 2022-06-01 K.OHWADA

CC=gcc
CCFLAGS=-Wall -c -fPIC
LIBFLAGS=-shared
LDFLAGS=-Wall -L./lib -lhello

TARGET=hello
MAIN_SRCS=main.c
LIBNAME=libhello.dylib
# LIB=lib/$(LIBNAME)
LIB=$(LIBNAME)
OBJ=objs/hello.o
SRC=sub/hello.c


$(TARGET): $(MAIN_SRCS) $(LIB)
	$(CC) $(MAIN_SRCS) $(LDFLAGS) -o bin/$@


$(LIB): $(OBJ)
	$(CC) $(OBJ) $(LIBFLAGS) -o $@


$(OBJ): $(SRC)
	$(CC) $< $(CCFLAGS) -o $@


install:
	cp $(LIB) /usr/local/lib/$(LIBNAME)


clean:
	rm -rf bin/*  objs/* lib/* /usr/local/lib/$(LIBNAME)

