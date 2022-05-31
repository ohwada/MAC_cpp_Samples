### 2022-05-01 K.OHWADA
### original : https://www.kushiro-ct.ac.jp/yanagawa/curses/cannon/
# change log
# 2022-05-01
# added branch of processing by OS

all: cannon

cannon: main.o object.o gameutil.o
ifeq ($(shell uname),Linux)
	gcc main.o object.o gameutil.o -lncurses -lm -o cannon
endif
ifeq  ($(shell uname),Darwin)
	gcc  main.c  object.c  gameutil.c -o cannon  `pkg-config --cflags --libs ncurses` 
endif

main.o: main.c object.h gameutil.h
	gcc -c main.c -Wall

object.o: object.c object.h
	gcc -c object.c -Wall

gameutil.o: gameutil.c gameutil.h
	cc -c gameutil.c -Wall

clean:
	rm *.o

