### make dynamic shared libraly
### 2022-06-01 K.OHWADA

CC=gcc
CCFLAGS=-Wall -c -fPIC
LIBFLAGS=-shared
LDFLAGS=-Wall -L./lib -lhello
DIR_GUARD=@mkdir -p $(@D)

TARGET=bin/hello
MAIN_SRCS=main.c
LIBNAME=libhello.dylib
LIB=lib/$(LIBNAME)
OBJ=objs/hello.o
SRC=sub/hello.c


$(TARGET): $(MAIN_SRCS) $(LIB)
	$(DIR_GUARD)
	$(CC) $(MAIN_SRCS) $(LDFLAGS) -o $@


$(LIB): $(OBJ)
	$(DIR_GUARD)
	$(CC) $(OBJ) $(LIBFLAGS) -o $@


$(OBJ): $(SRC)
	$(DIR_GUARD)
	$(CC) $< $(CCFLAGS) -o $@


install:
	cp $(LIB) /usr/local/lib/$(LIBNAME)


clean:
	rm -rf bin/*  objs/* lib/* /usr/local/lib/$(LIBNAME)

