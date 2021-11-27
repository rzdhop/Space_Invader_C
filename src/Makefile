all : PROJET EXECUTION

struct_def.o : struct_def.c struct_def.h
	gcc -c -Wall struct_def.c struct_def.h
	
key_pressed.o : key_pressed.c key_pressed.h
	gcc -c -Wall key_pressed.c key_pressed.h

linked_list.o : linked_list.c linked_list.h
	gcc -c -Wall linked_list.c linked_list.h

main.o : main.c
	gcc -pthread -c -Wall main.c

PROJET : main.o struct_def.o key_pressed.o linked_list.o
	gcc -pthread -o PROJET main.o struct_def.o key_pressed.o linked_list.o

EXECUTION :
	./PROJET

clean:
	rm  *.o
