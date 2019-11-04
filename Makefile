CC := gcc

all: main

main: main.o snake.o food.o
	$(CC) main.o snake.o food.o -o main -l ncursesw

main.o: vector.h main.c
	$(CC) main.c -c

snake.o: vector.h snake.h snake.c
	$(CC) snake.c -c

food.o: vector.h food.h food.c
	$(CC) food.c -c

clean:
	rm -f main *.o
