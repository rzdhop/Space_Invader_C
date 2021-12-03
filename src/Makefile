OBJS	= main.o struct_def.o key_pressed.o linked_list.o
SOURCE	= main.c struct_def.c key_pressed.c linked_list.c
HEADER	= struct_def.h key_pressed.h linked_list.h
OUT	= SpaceInvaders
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)
	./$(OUT)       #######comment this line to avoid automatic RUN#######

main.o: main.c
	$(CC) $(FLAGS) main.c 

struct_def.o: struct_def.c
	$(CC) $(FLAGS) struct_def.c 

key_pressed.o: key_pressed.c
	$(CC) $(FLAGS) key_pressed.c 

linked_list.o: linked_list.c
	$(CC) $(FLAGS) linked_list.c 


clean:
	rm -f $(OBJS) $(OUT)

#run: $(OUT)        #######to activate if the automatic RUN is disabled########
#	./$(OUT)