all : PROJET EXECUTION

struct_def.o : struct_def.c
	gcc -c -Wall struct_def.c

main.o : main.c
	gcc -c -Wall main.c

PROJET : main.o struct_def.o
	gcc -o PROJET main.o struct_def.o

EXECUTION :
	./PROJET
