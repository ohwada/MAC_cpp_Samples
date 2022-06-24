# Makefile for Brick Out

# by Bill Kendrick
# bill@newbreedsoftware.com
# http://www.newbreedsoftware.com/

# May 16, 2001 - June 9, 2002


CC=$(PROGPREFIX)gcc
STRIP=$(PROGPREFIX)strip

CFLAGS=-O2 -Wall -I/usr/include $(EXTRA_CFLAGS) -DIMAGEDIR=\"$(IMAGEDIR)\" \
	-DSOUNDDIR=\"$(SOUNDDIR)\" -DMUSICDIR=\"$(MUSICDIR)\"
XLIB=-L$(LIBDIR) -lX11 -lXpm

IMAGEDIR=images/
IMAGES=$(IMAGEDIR)ball.xpm \
  $(IMAGEDIR)brick1.xpm \
  $(IMAGEDIR)brick2.xpm \
  $(IMAGEDIR)brick3.xpm \
  $(IMAGEDIR)brick4.xpm \
  $(IMAGEDIR)brick5.xpm \
  $(IMAGEDIR)conton.xpm \
  $(IMAGEDIR)contoff.xpm \
  $(IMAGEDIR)done.xpm \
  $(IMAGEDIR)leftpipe.xpm \
  $(IMAGEDIR)launchoff.xpm \
  $(IMAGEDIR)launchon.xpm \
  $(IMAGEDIR)numbers.xpm \
  $(IMAGEDIR)paddle.xpm \
  $(IMAGEDIR)pause.xpm \
  $(IMAGEDIR)soundoff.xpm \
  $(IMAGEDIR)soundon.xpm \
  $(IMAGEDIR)start.xpm \
  $(IMAGEDIR)stats.xpm \
  $(IMAGEDIR)stats_leftpipe.xpm \
  $(IMAGEDIR)stats_rightpipe.xpm \
  $(IMAGEDIR)stats_toppipe.xpm \
  $(IMAGEDIR)title.xpm \
  $(IMAGEDIR)water.xpm

THE_IMAGES=$(IMAGES)


all:
	@echo "Pick a target:"
	@echo "--------------"
	@echo "host-x        - X-Window version for host environment (this computer)"
	@echo "host-sdl      - libSDL version for host envionrment"
	@echo "zaurus        - Qtopia/libSDL version for Sharp Zaurus PDA"
	@echo "mips-snow     - X-Window version for SNOW MIPS (Agenda VR3 PDA - newer Kernel)"
	@echo "mips-svr4     - X-Window version for SVR4 MIPS (Agenda VR3 PDA - older Kernel)"
	@echo

host-x:
	make \
		TARGET=brickout.host brickout.host \
		PROGPREFIX= \
		LIBDIR=/usr/X11R6/lib

host-sdl:
	make \
		TARGET=brickout.sdl brickout.sdl \
		PROGPREFIX= \
		XLIB="$(shell sdl-config --libs) -lSDL_mixer" \
		LIBDIR= \
		EXTRA_CFLAGS="-DUSE_SDL $(shell sdl-config --cflags)" \
		IMAGEDIR=images-sdl/ \
		SOUNDDIR=sounds/ \
		MUSICDIR=music/ \
		THE_IMAGES=

zaurus:
	make \
		TARGET=brickout.zaurus brickout.zaurus \
		PROGPREFIX=/usr/local/arm/bin/arm-linux- \
		XLIB="/usr/local/arm/lib/libSDL_mixer.a /usr/local/arm/lib/libSDL.a -L/usr/local/arm/lib/ -lpthread -L/opt/Qtopia/sharp/lib -lqpe -lqte" \
		LIBDIR= \
		EXTRA_CFLAGS="-DUSE_SDL $(shell sdl-config --cflags)" \
		IMAGEDIR=/opt/QtPalmtop/share/brickout/images/ \
		SOUNDDIR=/opt/QtPalmtop/share/brickout/sounds/ \
		MUSICDIR=/opt/QtPalmtop/share/brickout/music/ \
		THE_IMAGES=

mips-svr4:
	make \
		TARGET=brickout.mips brickout.mips \
		PROGPREFIX=mipsel-linux- \
		LIBDIR=/usr/mipsel-linux/lib/X11

mips-snow:
	make \
		TARGET=brickout.snow brickout.snow \
		PROGPREFIX=mipsel-linux- \
		EXTRA_CFLAGS="-B/opt/snow-gcc/lib/snow/" \
		LIBDIR=/opt/snow-gcc/lib/snow/

# used to be:	EXTRA_CFLAGS="-Os -B/opt/snow-gcc/lib/snow/" \

clean:
	-rm brickout.host brickout.mips brickout.snow \
		brickout.sdl brickout.zaurus


$(TARGET):	brickout.c $(THE_IMAGES)
	$(CC) $(CFLAGS) brickout.c $(XLIB) -o $(TARGET)
	$(STRIP) $(TARGET)
	$(STRIP) --remove-section .compact_rel $(TARGET)
	$(STRIP) --remove-section .note $(TARGET)
	$(STRIP) --remove-section .comment $(TARGET)
