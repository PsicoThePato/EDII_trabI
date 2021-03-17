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
        //printf("O NOME ATRIBUIDO FOI %s\n", pontoI->name);

    }

    else
    {
        pontoI->components[i-1] = atof(*(char **)arg);
        //printf("O NÚMERO ATRIBUIDO FOI %lf\n", pontoI->components[i-1]);

    }

}


int arestaComp(const void *aresta1, const void *aresta2)
{
    double dist1 = ((Aresta *)aresta1)->distAB;
    double dist2 = ((Aresta *)aresta2)->distAB;
    if(dist1 == dist2)
        return 0;
    else if(dist1 > dist2)
        return 1;
    else
        return -1;
}


void liberaPontos(Ponto *pontos, int dimensaoL)
{
    for(int i = 0; i < dimensaoL; i++)
    {
        free(pontos[i].name);
        free(pontos[i].components);
        
    }
    free(pontos);
}


int binarySearch(int *vetor, int piso, int teto, int x) 
{ 
    if(teto == -1)
        return -1;
    if(teto >= piso) 
    { 
        int mid = (teto + piso)/2; 
  
        if (vetor[mid] == x) 
            return mid; 
  
        if (vetor[mid] > x) 
            return binarySearch(vetor, piso, mid - 1, x); 
  
        return binarySearch(vetor, mid + 1, teto, x); 
    } 
    return -1; 
}


void ordenaPontos(Ponto *pontos, int k, int nLinhas)
{
    int latest_label_idx = -1;
    int labels[k];
    int gCount[k];
    int sCount[k];
    
    for(int i = 0; i < k; i ++)
    {
        gCount[i] = -1;
        sCount[i] = nLinhas/k;
    }
    
    char **groups[k];
    
    for(int i = 0; i < k; i++)
    {
        groups[i] = malloc(sizeof(char **) * nLinhas/k);
    }

    for(int i = 0; i < nLinhas; i++)
    {
        int grupo = pontos[i].pai;
        if(grupo == -1)
        {
            grupo = i;
        }
        
        int labelIdx = binarySearch(labels, 0, latest_label_idx, grupo);
        if(labelIdx == -1)
        {
            latest_label_idx++;
            labels[latest_label_idx] = grupo;
            labelIdx = latest_label_idx;
        }
        printf("O idx do grupo é %d\n", labelIdx);
        gCount[labelIdx]++;
        if(gCount[labelIdx] > sCount[labelIdx] - 1)
        {
            printf("Estou precisando dar um realloc\n");
            sCount[labelIdx] = sCount[labelIdx]*2;
            printf("ENDEREOC DO INFERNO DO PONTEIRO ANTES: %p\n", groups[labelIdx]);
            printf("INFERNO DO CARALHO DE ESPAÇOS %d\n", sCount[labelIdx]);
            groups[labelIdx] = (char **)realloc(groups[labelIdx], (sizeof(char **) * sCount[labelIdx]));
            printf("ENDEREOC DO INFERNO DO PONTEIRO DEPOIS: %p\n", groups[labelIdx]);
        }
        printf("Vou atribuir o ponto %s na posição [%d,%d]\n", pontos[i].name, labelIdx, gCount[labelIdx]);

        groups[labelIdx][gCount[labelIdx]] = pontos[i].name;
    }

    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j <= gCount[i]; j++)
        {
            printf("Minha contagem eh %d\n", gCount[i]);
            printf("VOU ACESSAR O PONTO [%d, %d]\n", i,j);
            printf("OLHA AQUI, CORNO %s\n", groups[i][j]);
        }
    }

}