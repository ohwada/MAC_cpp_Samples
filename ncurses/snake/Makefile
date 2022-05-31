### 2022-05-01 K.OHWADA

all: snake

snake: main.o fSnakeGameo
	g++ main.o fSnakeGame.o -lncurses -o snake

main.o: main.cpp fSnakeGame.h 
	g++ -c main.cpp -Wall

fSnakeGameo:  fSnakeGame.cpp fSnakeGame.h
	g++ -c fSnakeGame.cpp -Wall

clean:
	rm *.o

