#include "../headers/mathShit.h"

double euclidDist(double *vetor1, double *vetor2, int dimensao)
{
    double dist = 0;
    for(int i = 0; i < dimensao; i++)
    {
        printf("O valor do vator é %lf\n",vetor1[i]);
        dist += pow((vetor1[i] - vetor2[i]), 2);
        printf("A variávle dist atualmente tem o valor %lf\n", dist);
    }

    dist = sqrt(dist);

    return dist;
}