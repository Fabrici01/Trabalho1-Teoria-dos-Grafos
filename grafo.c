#include <stdio.h>
#include <stdlib.h>
#include "./header/fila.h"
#include "./header/grafo.h"

no* criarNo(int v){
    no *novoNo = (no*) malloc(sizeof(no));
    if(novoNo == NULL)
    {
        printf("Erro na alocacao do no\n");
        exit(1);
    }
    novoNo->vertice = v;
    novoNo->prox = NULL;
    return novoNo;
}

grafo* criarGrafo(int v){
    grafo* g = (grafo*) malloc(sizeof(grafo));
    if (g == NULL)
    {
        printf("Erro na alocacao do grafo\n");
        exit(1);
    }
    g->numVertices = v;
    g->listaAdj  = (no**) malloc(v * sizeof(no*));
    if (g->listaAdj == NULL)
    {
        printf("Erro na alocacao da lista de adjacencia\n");
        exit(1);
    }
    for (int i = 0; i < v; i++)
    {
        g->listaAdj[i] = NULL;
    }
    return g;
}

int existeAresta(no* inicio, int destino) {
    while (inicio != NULL) 
    {
        if (inicio->vertice == destino)
        {
            return 1;
        }
        inicio = inicio->prox;
    }
    return 0;
}

void addAresta(grafo* g, int origem, int destino, int direcionado){
//origem para destino
    if (!existeAresta(g->listaAdj[origem], destino + 1)) 
    {
        no* novoNo = criarNo(destino + 1);
        novoNo->prox = g->listaAdj[origem];
        g->listaAdj[origem] = novoNo;
    }
//destino para origem
    if (!direcionado) 
    {
        if (!existeAresta(g->listaAdj[destino], origem + 1)) 
        {
            no* novoNo = criarNo(origem + 1);
            novoNo->prox = g->listaAdj[destino];
            g->listaAdj[destino] = novoNo;
        }
    }
}

void imprimirCaminho(int origem, int destino, int *antecessor) {
    if (destino == origem) 
    {
        printf("%d", origem);
        return;
    }
    imprimirCaminho(origem, antecessor[destino-1], antecessor);
    printf(" -> %d", destino);
}

void buscaLargura(grafo *g, int origem, int destino) {
    fila *f = criarFila();
    int *visitado = (int*) calloc(g->numVertices, sizeof(int));
    if (!visitado) 
    {
        printf("Erro de alocacao no ponteiro visitado\n");
        liberarFila(f);
        exit(1);
    }
    int *antecessor = (int*) malloc(g->numVertices * sizeof(int));
    if (!antecessor) 
    {
        printf("Erro de alocacao no ponteiro antecessor\n");
        liberarFila(f);
        free(visitado);
        exit(1);
    }
    int cliques = 0;
    for (int i = 0; i < g->numVertices; i++) 
    {
        antecessor[i] = -1;
    }
    visitado[origem-1] = 1;
    inserirNaFila(f, origem);
    while (!filaVazia(f)) 
    {
        int atual = removerDaFila(f);

        if (atual == destino) 
        {
            break;
        }

        no* temp = g->listaAdj[atual-1];
        while (temp) 
        {
            int adj = temp->vertice;
            if (!visitado[adj-1]) 
            {
                visitado[adj-1] = 1;
                antecessor[adj-1] = atual;
                inserirNaFila(f, adj);
            }
            temp = temp->prox;
        }
    }
    liberarFila(f);
    for (int i = destino; i != origem; i = antecessor[i-1]) 
    {
        cliques++;
    }
    printf("\nMenor numeros de cliques de %d ate %d: %d\n", origem, destino, cliques);
    imprimirCaminho(origem, destino, antecessor);
    printf("\n");
    free(visitado);
    free(antecessor);
}

void liberarGrafo(grafo *g){
    if (g != NULL)
    {
        no *p, *temp;
        for (int i = 0; i < g->numVertices; i++)
        {
            for (p = g->listaAdj[i]; p != NULL; p = temp)
            {
                temp = p->prox;
                free(p);
            }
        }
        free(g->listaAdj);
        free(g);
    }
}