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
int find(Subset *subsets, int i);
void uniao(Subset *subsets, int xroot, int yroot);
Aresta* fazMst(Subset *subset, Aresta *arestas,int nLinhas, int nArestas, int k);

#endif