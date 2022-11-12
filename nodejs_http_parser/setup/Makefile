### make shared libraly
### 2022-06-01 K.OHWADA
### reference: https://github.com/nodejs/http-parser/blob/main/Makefile

CC=gcc
CFLAGS=-Wall -c -fPIC
LDFLAGS=-shared
OBJS=http_parser.o

VER=2.9.4
LIBNAME=libhttp_parser.$(VER)
PLATFORM ?= $(shell sh -c 'uname -s | tr "[A-Z]" "[a-z]"')

ifeq (darwin,$(PLATFORM))
TARGET=$(LIBNAME).dylib
else
TARGET=$(LIBNAME).so
endif


$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@


%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<


clean:
	rm -rf *.o

