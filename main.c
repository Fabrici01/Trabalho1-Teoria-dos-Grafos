#include <stdio.h>
#include <stdlib.h>
#define NCANAIS 100

struct No
{
    int vertice;
    struct No *prox;
}typedef no;

struct Grafo
{
    int numVertices;
    no **listaAdj;
}typedef grafo;

no* criarNo(int x){
    no *novoNo = malloc(sizeof(no));
    novoNo->vertice = x;
    novoNo->prox = NULL;
    return novoNo;
}

grafo* criarGrafo(int v){
    grafo* g = malloc(sizeof(grafo));
    g->numVertices = v;
    g->listaAdj  = malloc(v * sizeof(no));

    for (int i = 0; i < v; i++)
    {
        g->listaAdj[i] = NULL;
    }
    return g;
}

void addAresta(grafo* g, int origem, int destino, int direcionado){
//origem para destino
    no* novoNo = criarNo(destino);
    novoNo->prox = g->listaAdj[origem];
    g->listaAdj[origem] = novoNo;
//destino para origem
    if (!direcionado)
    {
        novoNo = criarNo(origem);
        novoNo->prox = g->listaAdj[destino];
        g->listaAdj[destino] = novoNo;
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
        }
    }
}

int main() {
//lendo o arquivo
    int atual, alvo, n;
    if (scanf("%d", &atual) == 0) {
        printf("Erro ao ler o arquivo\n");
    }
    if (scanf("%d", &alvo) == 0) {
        printf("EErro ao ler o arquivo\n");
    }
    if (scanf("%d", &n) == 0) {
        printf("Erro ao ler o arquivo\n");
    }
    while (getchar() != '\n' && !feof(stdin));
    int canaisAd[n];
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &canaisAd[i]) == 0) {
            printf("Erro ao ler o arquivo\n");
        }
    }
//criando o grafo
    
//algoritmo para determinar a distancia entre o canal atual e o canal desejado
    return 0;
}