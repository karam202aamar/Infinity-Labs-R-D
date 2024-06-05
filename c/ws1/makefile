string_test: string.o string_test.o
	gcc -Wall -ansi -pedantic string_test.o string.o -o string_test
string_test.o: string_test.c string.h
	gcc -c -Wall -ansi -pedantic string_test.c -o string_test.o
string.o: string.c string.h
	gcc -c -Wall -ansi -pedantic string.c -o string.o
