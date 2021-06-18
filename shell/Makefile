all: output

run: TURKSHELL
	./TURKSHELL

output: TURKSHELL.o parser.o
	gcc TURKSHELL.o parser.o -o TURKSHELL

TURKSHELL.o: TURKSHELL.c
	gcc -c TURKSHELL.c

parser.o: parser.c parser.h
	gcc -c parser.c

clean:
	rm *.o TURKSHELL
