mymake : graph.o parser.o
	gcc graph.o parser.o -o mymake
graph.o : graph.c graph.h
	gcc -Wall -g -c graph.c
parser.o : parser.c
	gcc -Wall -g -c parser.c
