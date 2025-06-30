#ifndef GRAFO_H
#define GRAFO_H
#include "./fila.h"

typedef struct Grafo
{
    int numVertices;
    no **listaAdj;
}grafo;

no* criarNo(int x);
grafo* criarGrafo(int v);
int existeAresta(no* inicio, int destino);
void addAresta(grafo* g, int origem, int destino, int direcionado);
void imprimirGrafo(grafo* g);
void imprimirCaminho(int origem, int destino, int *antecessor);
void buscaLargura(grafo *g, int tamanho, int origem, int destino);

#endif