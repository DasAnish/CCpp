FLAGS=-g -Wall --pedantic -std=c99
FLAG=-g -Wall --pedantic -std=c++98

all:
	gcc ${FLAGS} -c pcolparse.c
	g++ ${FLAG} -c extract.cc
	g++ ${FLAG} -o run pcolparse.o extract.o

clean:
	rm -f *.o
