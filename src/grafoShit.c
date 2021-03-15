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

int find(Ponto *pontos, int i)
{
    if(pontos[i].pai == -1)
    {
        return i;
    }
    
    return pontos[i].pai = find(pontos, pontos[i].pai);
}

void uniao(Ponto *pontos, int xroot, int yroot)
{
    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    
    if(pontos[xroot].rank < pontos[yroot].rank)
        pontos[xroot].pai = yroot;
    else if(pontos[xroot].rank > pontos[yroot].rank)
        pontos[yroot].pai = xroot;
 
    // If ranks are same, then make one as root and
    // increment its rank by one
    else 
    {
        pontos[yroot].pai = xroot;
        pontos[xroot].rank++;
    }
}


void fazMst(Ponto *pontos, Aresta *arestas,int nLinhas, int nArestas, int k)
{
    int i = 0, j = 0;
    int delimitador = nLinhas - k;
    while(i < delimitador && j < nArestas)
    {
        int paiA = find(pontos, arestas[j].pontoA);
        int paiB = find(pontos, arestas[j].pontoB);

        if(paiA != paiB)
        {
            uniao(pontos, paiA, paiB);
            i++;
        }
        else
        {
            j++;
        }

    }

}