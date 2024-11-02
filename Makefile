CFLAGS = -Wall -pedantic -ansi -g

box: box.o game.o random.o color.o terminal.o LinkedList.o
	gcc box.o game.o random.o color.o terminal.o LinkedList.o -o box

box.o: box.c header.h random.h color.h terminal.h linkedlist.h
	gcc -c box.c $(CFLAGS)

game.o: game.c header.h random.h color.h terminal.h linkedlist.h
	gcc -c game.c $(CFLAGS)

random.o: random.c
	gcc -c random.c

color.o: color.c
	gcc -c color.c

terminal.o: terminal.c
	gcc -c terminal.c

LinkedList.o: LinkedList.c linkedlist.h
	gcc -c LinkedList.c $(CFLAGS)
