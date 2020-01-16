FLAGS=-g -Wall --pedantic -std=c99
FLAG=-g -Wall --pedantic -std=c++98

all:
	gcc ${FLAGS} -c pcolparse.c
	g++ ${FLAG} -c decode.cpp
	g++ ${FLAG} -o run pcolparse.o decode.o

clean:
	rm -f decode.o run
