all : PROJET EXECUTION

struct_def.o : struct_def.c struct_def.h
	gcc -c -Wall -Wno-unused-variable struct_def.c struct_def.h
	
key_pressed.o : key_pressed.c key_pressed.h
	gcc -c -Wall -Wno-unused-variable key_pressed.c key_pressed.h

linked_list.o : linked_list.c linked_list.h
	gcc -c -Wall -Wno-unused-variable linked_list.c linked_list.h

leak_detector_c.o :
	gcc -c -Wall -Wno-unused-variable leakdetector/leak_detector_c.c leakdetector/leak_detector_c.h

main.o : main.c
	gcc -pthread -c -Wall -Wno-unused-variable main.c

PROJET : main.o struct_def.o key_pressed.o linked_list.o
	gcc -pthread -o PROJET main.o struct_def.o key_pressed.o linked_list.o leak_detector_c.o

EXECUTION :
	./PROJET

clean:
	rm  *.o
