#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/ponto.h"
#include "../headers/dbg.h"

void alocaColunas(Ponto *pontoI, int nLinhas, int nColunas)
{
    for(int i = 0; i < nLinhas; i++)
    {
        pontoI[i].components = malloc(sizeof(double) *nColunas);
        if(pontoI[i].components == NULL)
        {
            printf("Lekao, deu bom n\n");
            exit(1);
        }
    }
}



void atribuipIDX(Ponto *pontoI, int i, void *arg)
{
    if(i == 0) 
    {
        pontoI->name = strdup(*(char **)arg);
        //pontoI->name = strdup("TESTE");
        printf("O NOME ATRIBUIDO FOI %s\n", pontoI->name);

    }

    else
    {
        pontoI->components[i-1] = atof(*(char **)arg);
        printf("O NÚMERO ATRIBUIDO FOI %lf\n", pontoI->components[i-1]);

    }

}