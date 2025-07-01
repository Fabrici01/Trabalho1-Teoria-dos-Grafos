#include <stdio.h>
#include <stdlib.h>
#include "./header/fila.h"

fila* criarFila(){
    fila *f = (fila*)malloc(sizeof(fila));
    if(f==NULL){
        printf("Erro na alocacao da fila\n");
        exit(1);
    }
    f->inicio = f->fim = NULL;
    return f;
}

int filaVazia(fila* f){
    return (f->inicio == NULL);
}

void inserirNaFila(fila* f, int v){
    no *novo = criarNo(v);
    if(filaVazia(f)){
        f->inicio = novo;
    }
    else{
        f->fim->prox = novo;
    }
    f->fim = novo;
}

int removerDaFila(fila* f){
    int rem = 0;
    if(filaVazia(f)){
        printf("Lista vazia\n");
    }
    else{
        rem = f->inicio->vertice;
        no *temp;
        temp = f->inicio;
        if(temp->prox == NULL)
            f->fim = NULL;
        f->inicio = temp->prox;
        free(temp);
    }
    return rem;
}

void liberarFila(fila* f){
    if (!filaVazia(f))
    {
        no *p, *temp;
        for (p = f->inicio; p != NULL; p = temp)
        {
            temp = p->prox;
            free(p);
        }
        free(f);
    }
}