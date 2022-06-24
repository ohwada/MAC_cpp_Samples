# Makefile for PDA Maze

# by Bill Kendrick
# bill@newbreedsoftware.com
# http://www.newbreedsoftware.com/

# May 23, 2001 - September 4, 2001


CC=$(PROGPREFIX)gcc
STRIP=$(PROGPREFIX)strip

CFLAGS=-O2 -Wall -I/usr/include $(EXTRA_CFLAGS)
XLIB=-L$(LIBDIR) -lX11 -lXpm

IMAGES=$(shell /bin/ls images/*.xpm)


all:	host mips-snow

host:
	make \
		TARGET=pdamaze.host pdamaze.host \
		PROGPREFIX= \
		LIBDIR=/usr/X11R6/lib

mips-svr4:
	make \
		TARGET=pdamaze.mips pdamaze.mips \
		PROGPREFIX=mipsel-linux- \
		LIBDIR=/usr/mipsel-linux/lib/X11

mips-snow:
	make \
		TARGET=pdamaze.snow pdamaze.snow \
		PROGPREFIX=mipsel-linux- \
		EXTRA_CFLAGS="-Os -B/opt/snow-gcc/lib/snow/" \
		LIBDIR=/opt/snow-gcc/lib/snow


clean:
	-rm pdamaze.host pdamaze.mips pdamaze.snow


$(TARGET):	pdamaze.c $(IMAGES)
	$(CC) $(CFLAGS) pdamaze.c $(XLIB) -o $(TARGET)
	$(STRIP) $(TARGET)
	$(STRIP) --remove-section .compact_rel $(TARGET)
	$(STRIP) --remove-section .note $(TARGET)
	$(STRIP) --remove-section .comment $(TARGET)
