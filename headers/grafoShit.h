#ifndef _GRAFOSHIT_h_
#define _GRAFOSHIT_h_

#include "ponto.h"
#include <stdlib.h>


typedef struct grafo
{
    int nLinhas;
    int nArestas;
    Aresta *arestas;
}Grafo;

typedef struct subset
{
    int pai;
    int rank;
}Subset;


Grafo* criaGrafo(int nLinhas, int nArestas, Aresta* arestas);
int find(Ponto *pontos, int i);
void uniao(Ponto *pontos, int xroot, int yroot);
void fazMst(Ponto *pontos, Aresta *arestas,int nLinhas, int nArestas, int k);

#endif