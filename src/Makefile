all : PROJET EXECUTION

struct_def.o : struct_def.c struct_def.h
	gcc -c -Wall struct_def.c struct_def.h
	
key_pressed.o : key_pressed.c key_pressed.h
	gcc -c -Wall key_pressed.c key_pressed.h

main.o : main.c
	gcc -c -Wall main.c

PROJET : main.o struct_def.o key_pressed.o
	gcc -o PROJET main.o struct_def.o key_pressed.o

EXECUTION :
	./PROJET
