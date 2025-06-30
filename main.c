#include <stdio.h>
#include <stdlib.h>
#include "./header/fila.h"
#include "./header/grafo.h"
#define NCANAIS 100

int main(int argc, char const *argv[])
{
//lendo o arquivo
    int atual, alvo, n;

    if(scanf("%d %d %d", &atual, &alvo, &n) != 3) {
        printf("Erro ao ler os dados\n");
    }

    while (getchar() != '\n' && getchar() != EOF);

    printf("\nCanal atual: %d\nCanal alvo: %d\nQuantidade de canais adultos: %d\n", atual, alvo, n);

    int canalAdulto[NCANAIS];
    for (int i = 0; i < NCANAIS; i++)
    {
        canalAdulto[i] = 0;
    }
    printf("Canais adultos: ");
    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        if (scanf("%d", &temp) == 0) {
            printf("Erro ao ler os dados\n");
        }
        printf("%d, ", temp);
        canalAdulto[temp-1] = 1;
    }
    printf("\n");
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
    buscaLargura(canais, NCANAIS, atual, alvo);
    return 0;
}