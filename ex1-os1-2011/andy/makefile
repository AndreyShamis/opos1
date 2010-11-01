ex1: 	main.o mem.o  
		gcc main.o mem.o -o ex1

mem.o:	mem.c mem.h
		gcc -Wall -c mem.c
main.o:	main.c mem.h
		gcc -Wall -c main.c
