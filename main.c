#include <stdio.h>
#include <stdlib.h>
#define NCANAIS 100

typedef struct No
{
    int vertice;
    struct No *prox;
}no;

typedef struct Grafo
{
    int numVertices;
    no **listaAdj;
}grafo;

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
    for (int i = 0; i < g->numVertices; i++)
    {
        no* temp = g->listaAdj[i];
        printf("Canal %d: ", i+1);
        while (temp)
        {
            printf("%d -> ", temp->vertice);
            temp = temp->prox; // <<< Adicionado
        }
        printf("NULL\n");
    }
}


int main(int argc, char const *argv[])
{
//lendo o arquivo
    if (argc != 2)
    {
        printf("\nUEPA\n");
        exit(EXIT_FAILURE);
    }
    
    int atual, alvo, n;

    FILE *arq = fopen(argv[1], "r");

    if (fscanf(arq, "%d %d %d", &atual, &alvo, &n) != 3) {
        printf("Erro ao ler os dados\n");
    }

    printf("\nCanal atual: %d\nCanal alvo: %d\nQuantidade de canais adultos: %d\n", atual, alvo, n);

    int canalAdulto[NCANAIS];
    for (int i = 0; i < NCANAIS; i++)
    {
        canalAdulto[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        if (fscanf(arq, "%d", &temp) == 0) {
            printf("Erro ao ler os dados\n");
        }
        printf("Canal adulto: %d\n", temp);
        canalAdulto[temp-1] = 1;
    }
    fclose(arq);
//criando o grafo
    grafo *canais = criarGrafo(NCANAIS);
    if (!canalAdulto[NCANAIS-1] && !canalAdulto[0])
    {
        addAresta(canais, NCANAIS-1, 0, 0);
    }
    for (int i = 1; i < NCANAIS; i++)
    {
        if (!canalAdulto[i-1])
        {
            int dobro = (2*i)-1, triplo = (3*i) - 1;
        //Botões +1 e -1
            if (!canalAdulto[i])
            {
                addAresta(canais, i-1, i, 0);
            }
        //Botões *2 e /2
            if (dobro <= NCANAIS && !canalAdulto[dobro])
            {
                addAresta(canais, i-1, dobro, 0);
            }
        //Botão *3
            if (triplo <= NCANAIS && !canalAdulto[triplo])
            {
                addAresta(canais, i-1, triplo, 1);
            }
        }
    }
    imprimirGrafo(canais);
//algoritmo para determinar a distancia entre o canal atual e o canal desejado
    return 0;
}