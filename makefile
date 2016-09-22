main: main.o matrix.o
	gcc main.o matrix.o -o main
main.o: main.c matrix.h
	gcc -c main.c -o main.o
matrix.o: matrix.c matrix.h
	gcc -c matrix.c -o matrix.o
clean:
	rm -rf *.o main


