#ifndef FILA_H
#define FILA_H

typedef struct No{
    int vertice;
    struct No *prox;
}no;

typedef struct Fila{
    no *inicio, *fim;
}fila;

fila* criarFila();
int filaVazia(fila* f);
void inserirNaFila(fila* f, int v);
int removerDaFila(fila* f);
void liberarFila(fila* f);

#endif