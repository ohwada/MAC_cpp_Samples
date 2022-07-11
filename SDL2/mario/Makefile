### change log
### 2022-06-01 K.OHWADA
### add mac
### use -std=c99 instead of -ansi in OPTS

FILES=src/main.c src/GameState.c src/MainState.c src/JeuState.c src/Mario.c
LIBSW=-lmingw32 -lSDLmain -lSDL.dll -lSDL_image
LIBSU=-lSDLmain -lSDL -lSDL_image

# for Mac
LIBSM=-lSDLmain -lSDL -lSDL_image -framework Cocoa

OPTS=-Wall -Wextra -std=c99 -pedantic -iquoteinclude
OUTPUT=SMB

all:
	gcc $(OPTS) $(FILES) -mwindows $(LIBSW) -o $(OUTPUT)

unix:
	gcc $(OPTS) $(FILES) $(LIBSU) -o $(OUTPUT)

mac:
	gcc $(OPTS) $(FILES) $(LIBSM) -o $(OUTPUT)
