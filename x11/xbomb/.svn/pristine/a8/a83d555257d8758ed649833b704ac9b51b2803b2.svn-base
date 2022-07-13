# $Header: /home/amb/CVS/xbomb/Makefile,v 1.13 1996-01-20 21:02:46 amb Exp $
#
# XBomb - 'Minesweeper' game - Version 2
#
# Makefile.
#
# Written by Andrew M. Bishop
#
# This file Copyright 1994 1995 Andrew M. Bishop
# It may be distributed under the GNU Public License, version 2, or
# any higher version.  See section COPYING of the GNU Public license
# for conditions under which this file may be redistributed.
#

CC=gcc
CFLAGS=-O2

INCLUDES=

LIB=

XLIB=-L/usr/X11R6/lib -lXaw -lXmu -lXt -lX11

COMPILE=$(CC) -c $(CFLAGS)

LINK=$(CC)

OBJ=xbomb.o xwindow.o hiscore.o

INSTDIR=/usr/local

########

xbomb : $(OBJ)
	$(LINK) $(OBJ) -o $@ $(LIB) $(XLIB)

########

%.o : %.c
	$(COMPILE) $< -o $@ $(INCLUDES)

xbomb.o   : xbomb.c   xbomb.h
xwindow.o : xwindow.c xbomb.h icon.h
hiscore.o : hiscore.c xbomb.h

########

clean :
	-rm -f *.o *~ core

########

install :
	strip xbomb
	install -d $(INSTDIR)/bin
	install -d $(INSTDIR)/man/man6
	install -d $(INSTDIR)/lib/app-defaults
	install -m 755 xbomb $(INSTDIR)/bin
	install -m 644 xbomb.6 $(INSTDIR)/man/man6
	install -m 644 xbomb.ad $(INSTDIR)/lib/app-defaults/XBomb
