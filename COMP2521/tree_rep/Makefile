CC=gcc
FLAGS=-Wall -Werror

main : main.o tree.o 
	$(CC) -o main main.o tree.o 
	
tree.o : tree.c 
	$(CC) $(FLAGS) -c tree.c

main.o : main.c tree.c
	$(CC) $(FLAGS) -c main.c

clean : 
	rm -f *.o main

