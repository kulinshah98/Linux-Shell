CC=gcc
CFLAGS=-I
all: myshell
myshell: readaline.o shellprompt.o execute.o shell.o pipelining.o
	$(CC) -o myshell shellprompt.o readaline.o execute.o shell.o pipelining.o

shell.o: shell.c shell.h
	$(CC) -c shell.c

readaline.o: readaline.c readaline.h
	$(CC) -c readaline.c

shellprompt.o: shellprompt.c shellprompt.h
	$(CC) -c shellprompt.c

execute.o: execute.c execute.h
	$(CC) -c execute.c

pipelining.o: pipelining.c pipelining.h
	$(CC) -c pipelining.c
