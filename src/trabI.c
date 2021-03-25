#include <stdio.h>

#include "../headers/ponto.h"
#include "../headers/fileShit.h"
#include "../headers/grafoShit.h"
#include "../headers/mathShit.h"


int main(int argc, char**argv)
{
    if(argc != 4)
    {
        printf("Número bizarro de argumentos de entrada\n");
        exit(1);
    }
    char *arqEntrada = argv[1];
    int k = atoi(argv[2]);
    char *arqSaida = argv[3];


    int linhas = pegaDimensoesL(arqEntrada);
    int colunas = pegaDimensoesC(arqEntrada);
    Ponto *pontos = leEntrada(arqEntrada, linhas, colunas);

    int nArestas = (linhas * (linhas - 1))/2;
    Aresta *arestas = wtArestas(pontos, linhas, colunas, nArestas);
    qsort(arestas, nArestas, sizeof(Aresta), &arestaComp);
    fazMst(pontos, arestas, linhas, nArestas, k);
    free(arestas);

    escreveArquivo(pontos, k, linhas, arqSaida);
    liberaPontos(pontos, linhas);
}