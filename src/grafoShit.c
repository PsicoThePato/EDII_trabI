#include "../headers/grafoShit.h"
#include <stdio.h>

Grafo* criaGrafo(int nLinhas, int nArestas, Aresta* arestas)
{
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->nLinhas = nLinhas;
    grafo->nArestas = nArestas;
    grafo->arestas = arestas;
 
    return grafo;
}

int find(Subset *subsets, int i)
{
    if(subsets[i].pai == -1)
    {
        return i;
    }
    
    if(subsets[i].pai != i)
    {
        subsets[i].pai = find(subsets, subsets[i].pai);
    }
 
    return subsets[i].pai;
}

void uniao(Subset *subsets, int xroot, int yroot)
{
    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if(subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].pai = yroot;
    else if(subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].pai = xroot;
 
    // If ranks are same, then make one as root and
    // increment its rank by one
    else 
    {
        subsets[yroot].pai = xroot;
        subsets[xroot].rank++;
    }
}


Aresta* fazMst(Subset *subset, Aresta *arestas,int nLinhas, int nArestas, int k)
{
    int i = 0, j = 0;
    int delimitador = nLinhas - k;
    Aresta *movimentoSemTerra = malloc(sizeof(Aresta) * delimitador);
    while(i < delimitador && j < nArestas)
    {
        int paiA = find(subset, arestas[j].pontoA);
        int paiB = find(subset, arestas[j].pontoB);

        if(paiA != paiB)
        {
            uniao(subset, paiA, paiB);
            movimentoSemTerra[i] = arestas[j];
            i++;
        }
        j++;

    }

    return movimentoSemTerra;
}