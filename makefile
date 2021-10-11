exec: main.o dicionario.o
	gcc -o exec main.o dicionario.o

main.o: main.c dicionario.h
	gcc -c main.c

dicionario.o: dicionario.c dicionario.h
	gcc -c dicionario.c