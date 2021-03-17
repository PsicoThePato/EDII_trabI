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


void inicializaMatrizGruposPontos(int *labels, int *gCount, char ***groups, Ponto *pontos, int nLinhas, int k, Grupo *grupos)
{
    int sCount[k];
    int latest_label_idx = -1;
    
    for(int i = 0; i < k; i ++)
    {
        gCount[i] = -1;
        sCount[i] = nLinhas/k;
    }

    for(int i = 0; i < k; i++)
    {
        grupos[i].nomePontos = malloc(sizeof(char **) * nLinhas/k);
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
}

int compPontos(const void *ponto1, const void *ponto2)
{
    char *nomePonto1 = ((Ponto *)ponto1)->name;
    char *nomePonto2 = ((Ponto *)ponto2)->name;
    return(strcmp(nomePonto1, nomePonto2));
}

int compGrupos(const void *grupo1, const void *grupo2)
{
    char *pElemGrupo1 = *((char ***)grupo1)[0];
    char *pElemGrupo2 = *((char ***)grupo2)[0];
    printf("ESTOU COMPARANDO OS PONTOS %s e %s\n", pElemGrupo1, pElemGrupo2);
    return(strcmp(pElemGrupo1, pElemGrupo2));
}

void ordenaPontos(Ponto *pontos, int k, int nLinhas)
{
    int labels[k];
    int gCount[k];
    char **groups[k];
    Grupo zap[k];

    inicializaMatrizGruposPontos(labels, gCount, groups, pontos, nLinhas, k);
    FILE *fp = fopen("out/teste.txt", "w+");
    for(int i = 0; i < k; i++)
    {
        qsort(groups[i], gCount[i]+1, sizeof(char*), &compPontos);
    }

    printf("TESTE %s\n", groups[0][0]);
    qsort(groups, k, sizeof(char**), &compGrupos);
     for(int i = 0; i < k; i++)
    {
        printf("O grupo é %d\n", i);
        for(int j = 0; j <= gCount[i]; j++)
        {
            printf("O PONTO é %s\n", groups[i][j]);
            fprintf(fp, "%s,", groups[i][j]);
        }
        fputc('\n', fp);
    }
    fclose(fp);

    for(int i = 0; i < k; i++)
    {
        free(groups[i]);
    }
}