#include <stdio.h>
#include <stdlib.h>
#include "./header/fila.h"
#include "./header/grafo.h"

no* criarNo(int x){
    no *novoNo = malloc(sizeof(no));
    novoNo->vertice = x;
    novoNo->prox = NULL;
    return novoNo;
}

grafo* criarGrafo(int v){
    grafo* g = malloc(sizeof(grafo));
    g->numVertices = v;
    g->listaAdj  = malloc(v * sizeof(no*));

    for (int i = 0; i < v; i++)
    {
        g->listaAdj[i] = NULL;
    }
    return g;
}

int existeAresta(no* inicio, int destino) {
    while (inicio != NULL) {
        if (inicio->vertice == destino)
            return 1;
        inicio = inicio->prox;
    }
    return 0;
}

void addAresta(grafo* g, int origem, int destino, int direcionado){
//origem para destino
    if (!existeAresta(g->listaAdj[origem], destino + 1)) {
        no* novoNo = criarNo(destino + 1);
        novoNo->prox = g->listaAdj[origem];
        g->listaAdj[origem] = novoNo;
    }
//destino para origem
    if (!direcionado) {
        if (!existeAresta(g->listaAdj[destino], origem + 1)) {
            no* novoNo = criarNo(origem + 1);
            novoNo->prox = g->listaAdj[destino];
            g->listaAdj[destino] = novoNo;
        }
    }
}

void imprimirGrafo(grafo* g){
    printf("\n");
    for (int i = 0; i < g->numVertices; i++)
    {
        no* temp = g->listaAdj[i];
        printf("Canal %d: ", i+1);
        while (temp)
        {
            printf("%d -> ", temp->vertice);
            temp = temp->prox;
        }
        printf("NULL\n");
    }
}

void imprimirCaminho(int origem, int destino, int *antecessor) {
    if (destino == origem) {
        printf("%d", origem);
        return;
    }
    imprimirCaminho(origem, antecessor[destino-1], antecessor);
    printf(" -> %d", destino);
}

void buscaLargura(grafo *g, int tamanho, int origem, int destino) {
    fila *f = criarFila();
    int *visitado = (int*) calloc(tamanho, sizeof(int));
    int *antecessor = (int*) malloc(tamanho * sizeof(int));

    if (!visitado) {
        printf("Erro de alocacao no ponteiro visitado\n");
        exit(EXIT_FAILURE);
    }
    if (!antecessor) {
        printf("Erro de alocacao no ponteiro antecessor\n");
        free(visitado);
        exit(EXIT_FAILURE);
    }

    int cliques = 0;

    for (int i = 0; i < tamanho; i++) {
        antecessor[i] = -1;
    }

    visitado[origem-1] = 1;
    inserirNaFila(f, origem);
    while (!filaVazia(f)) {
        int atual = removerDaFila(f);

        if (atual == destino) {
            break;
        }

        no* temp = g->listaAdj[atual-1];
        while (temp) {
            int adj = temp->vertice;
            if (!visitado[adj-1]) {
                visitado[adj-1] = 1;
                antecessor[adj-1] = atual;
                inserirNaFila(f, adj);
            }
            temp = temp->prox;
        }
    }
    liberarFila(f);
    for (int i = destino; i != origem; i = antecessor[i-1]) {
        cliques++;
    }
    printf("\nMenor numeros de cliques de %d ate %d: %d\n", origem, destino, cliques);
    imprimirCaminho(origem, destino, antecessor);
    printf("\n");

    free(visitado);
    free(antecessor);
}