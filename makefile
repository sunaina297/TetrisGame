CC_C = g++
CFLAGS = -Wall -g -std=c++11
LIBS= -lglut -lGL -lGLU

all: a1



%.o : %.c
	$(CC_C) -c $(CFLAGS) $<

a1: FruitTetris.o helper.o backboard.o play.o tetromino.o
	$(CC_C) -o FruitTetris FruitTetris.o helper.o backboard.o play.o tetromino.o $(LIBS)



clean:
	rm Fruittetris.o
	rm helper.o
	rm backboard.o
	rm play.o
	rm tetromino.o
