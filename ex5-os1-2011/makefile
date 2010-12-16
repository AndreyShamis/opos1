all:		mem.o ex4a.o  ex4b.o shell.o
			gcc mem.o shell.o ex4a.o -o ex4a
			gcc mem.o shell.o ex4b.o -o ex4b

ex4a.o:		ex4a.c ex4a.h
			gcc -Wall -c ex4a.c
ex4b.o:		ex4b.c ex4b.h
			gcc -Wall -c ex4b.c
			
shell.o:	shell.c shell.h
			gcc -Wall -c shell.c

mem.o:		mem.c mem.h
			gcc -Wall -c mem.c 

