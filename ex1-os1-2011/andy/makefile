ex1: 	main.o mem.o sort.o read.o write.o
		gcc main.o mem.o sort.o read.o write.o -o ex1

sort.o:	sort.c sort.h
		gcc -Wall -c sort.c
mem.o:	mem.c mem.h
		gcc -Wall -c mem.c
read.o:	read.c read.h mem.h
		gcc -Wall -c read.c
write.o:	write.c write.h
		gcc -Wall -c write.c
main.o:	main.c mem.h sort.h read.h
		gcc -Wall -c main.c
