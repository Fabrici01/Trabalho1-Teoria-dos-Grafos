#ifndef GRAFO_H
#define GRAFO_H

typedef struct No{
    int vertice;
    struct No *prox;
}no;

typedef struct Grafo
{
    int numVertices;
    no **listaAdj;
}grafo;

no* criarNo(int x);
grafo* criarGrafo(int v);
int existeAresta(no* inicio, int destino);
void addAresta(grafo* g, int origem, int destino, int direcionado);
void imprimirCaminho(int origem, int destino, int *antecessor);
void buscaLargura(grafo *g, int origem, int destino);
void liberarGrafo(grafo *g);

#endif