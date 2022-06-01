### 2022-05-01 K.OHWADA
### original : https://www.kushiro-ct.ac.jp/yanagawa/curses/cannon/

all: cannon

cannon: main.o object.o gameutil.o
	gcc main.o object.o gameutil.o -lncurses -lm -o cannon

main.o: main.c object.h gameutil.h
	gcc -c main.c -Wall

object.o: object.c object.h
	gcc -c object.c -Wall

gameutil.o: gameutil.c gameutil.h
	cc -c gameutil.c -Wall

clean:
	rm *.o

