a03: main.o memcheck.o
	gcc -g -Wall -ansi -pedantic -include memcheck.h main.o memcheck.o -o a03run

memcheck.o: memcheck.c
	gcc -g -Wall -ansi -pedantic -c memcheck.c -o memcheck.o

main.o: main.c memcheck.h
	gcc -g -Wall -ansi -pedantic -include memcheck.h -c main.c -o main.o

clean:
	rm -i a03run main.o memcheck.o
