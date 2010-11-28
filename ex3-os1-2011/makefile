all:		mem.o ex1a.o ex1b.o shell.o
			gcc mem.o shell.o ex1a.o -o ex1a
			gcc mem.o shell.o ex1b.o -o ex1b

ex1a.o:		ex1a.c ex1a.h
			gcc -Wall -c ex1a.c

ex1b.o:		ex1b.c ex1b.h
			gcc -Wall -c ex1b.c

shell.o:	shell.c shell.h
			gcc -Wall -c shell.c

mem.o:		mem.c mem.h
			gcc -Wall -c mem.c 

