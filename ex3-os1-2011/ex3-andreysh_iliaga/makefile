all:		mem.o ex3a.o ex3b.o shell.o
			gcc mem.o shell.o ex3a.o -o ex3a
			gcc mem.o shell.o ex3b.o -o ex3b

ex3a.o:		ex3a.c ex3a.h
			gcc -Wall -c ex3a.c

ex3b.o:		ex3b.c ex3b.h
			gcc -Wall -c ex3b.c

shell.o:	shell.c shell.h
			gcc -Wall -c shell.c

mem.o:		mem.c mem.h
			gcc -Wall -c mem.c 

