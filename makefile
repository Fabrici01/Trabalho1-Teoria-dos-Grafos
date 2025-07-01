all: compila

compila: main.o fila.o grafo.o
	gcc main.o fila.o grafo.o -o prog

main.o: main.c
	gcc -c main.c

fila.o: fila.c
	gcc -c fila.c

grafo.o: grafo.c 
	gcc -c grafo.c

clean:
	rm -f main.o fila.o grafo.o prog