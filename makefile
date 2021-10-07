exec: main.o cabecalho.o
	gcc -o exec main.o cabecalho.o

main.o: main.c cabecalho.h
	gcc -c main.c

cabecalho.o: cabecalho.c cabecalho.h
	gcc -c cabecalho.c