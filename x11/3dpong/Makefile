# Makefile for 3dpong

# by Bill Kendrick
# bill@newbreedsoftware.com

# New Breed Software
# http://www.newbreedsoftware.com/3dpng/

# December 9, 1997 - April 24, 2004


# Makefile user-definable variables

CC=gcc
CFLAGS=-I/usr/X11R6/include
MATHLIB=-lm


# Where to install things:

PREFIX=/usr/local
BIN_PREFIX=$(PREFIX)/bin
MAN_PREFIX=$(PREFIX)/man


# adjust according to target
XLIB=-L/usr/X11R6/lib -lX11

# uncomment for sunos/solaris
#XLIB=-L/usr/openwin/lib -lX11

# uncomment for FreeBSD
#XLIB=-L /usr/X11R6/lib -lX11 -lcompat


# Makefile other variables

OBJECTS=obj/3dpong.o obj/window.o obj/connect.o obj/hints.o obj/visual.o \
	obj/gc.o obj/color.o obj/randnum.o obj/text.o


# Makefile commands: 

all:	3dpong

install:	3dpong
	install -d $(BIN_PREFIX)
	cp 3dpong $(BIN_PREFIX)/
	chmod 755 $(BIN_PREFIX)/3dpong
	cp examples/3dpong-vs-computer.sh $(BIN_PREFIX)/
	chmod 755 $(BIN_PREFIX)/3dpong-vs-computer.sh
	cp examples/3dpong-handball.sh $(BIN_PREFIX)/
	chmod 755 $(BIN_PREFIX)/3dpong-handball.sh
	install -d $(MAN_PREFIX)/man6
	cp src/3dpong.6 $(MAN_PREFIX)/man6/
	chmod 644 $(MAN_PREFIX)/man6/3dpong.6

uninstall:
	-rm $(BIN_PREFIX)/3dpong
	-rm $(BIN_PREFIX)/3dpong-vs-computer.sh
	-rm $(BIN_PREFIX)/3dpong-handball.sh
	-rm $(MAN_PREFIX)/man6/3dpong.6

clean:
	-rm 3dpong
	-rm obj/*.o


# Application:

3dpong:	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(XLIB) $(MATHLIB) -o 3dpong


# Application object:

obj/3dpong.o:	src/3dpong.c src/window.h src/connect.h src/hints.h \
		src/visual.h src/gc.h src/color.h src/randnum.h src/text.h
	$(CC)	$(CFLAGS) src/3dpong.c -c -o obj/3dpong.o


# Library objects:

obj/window.o:	src/window.c src/window.h
	$(CC)	$(CFLAGS) src/window.c -c -o obj/window.o
 
obj/connect.o:	src/connect.c src/connect.h
	$(CC)	$(CFLAGS) src/connect.c -c -o obj/connect.o

obj/hints.o:	src/hints.c src/hints.h
	$(CC)	$(CFLAGS) src/hints.c -c -o obj/hints.o

obj/visual.o:	src/visual.c src/visual.h
	$(CC)	$(CFLAGS) src/visual.c -c -o obj/visual.o

obj/gc.o:	src/gc.c src/gc.h
	$(CC)	$(CFLAGS) src/gc.c -c -o obj/gc.o

obj/color.o:	src/color.c src/color.h
	$(CC)	$(CFLAGS) src/color.c -c -o obj/color.o

obj/randnum.o:	src/randnum.c src/randnum.h
	$(CC)	$(CFLAGS) src/randnum.c -c -o obj/randnum.o

obj/text.o:	src/text.c src/text.h
	$(CC)	$(CFLAGS) src/text.c -c -o obj/text.o

