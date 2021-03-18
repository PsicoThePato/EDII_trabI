#include <stdio.h>
#include <stdlib.h>

#include "../headers/mathShit.h"


double euclidDist(double *vetor1, double *vetor2, int dimensao)
{
    double dist = 0;
    for(int i = 0; i < dimensao; i++)
    {
        // if(vetor1[i] > vetor2[i])
        //     dist += vetor1[i] - vetor2[i];
        // else
        //     dist += vetor2[i] - vetor1[i];
        //dist += pow((vetor1[i] - vetor2[i]), 2);
        dist += (vetor1[i] - vetor2[i]) * (vetor1[i] - vetor2[i]);
    }

    //dist = sqrt(dist);

    return dist;
}


Aresta* wtArestas(Ponto* pontos, int dimensaoL, int dimensaoC, int nArestas)
{
    Aresta *grafo = malloc(sizeof(Aresta) * nArestas);
    int cont = 0;
    for(int i = 0; i < dimensaoL - 1; i++)
    {
        for(int j = i+1; j < dimensaoL; j++)
        {
            double distAB = euclidDist(pontos[i].components, pontos[j].components, dimensaoC);
            grafo[cont].pontoA = i;
            grafo[cont].pontoB = j;
            grafo[cont].distAB = distAB;
            cont++;
        }
    }

    return grafo;
}

