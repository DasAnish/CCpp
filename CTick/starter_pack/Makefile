FLAGS=-g -Wall --pedantic -std=c99
FLAG=-g -Wall --pedantic -std=c++98

all:
	gcc ${FLAGS} -c pcolparse.c
	gcc ${FLAGS} -c summary.c
	gcc ${FLAGS} -o summary summary.o pcolparse.o
	g++ ${FLAG} -c extract.cc
	g++ ${FLAG} -o run extract.o pcolparse.o
