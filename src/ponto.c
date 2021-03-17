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


void inicializaMatrizGruposPontos(Grupo *grupos, Ponto *pontos, int nLinhas, int k)
{
    int labels[k];
    int sCount[k];
    int latest_label_idx = -1;

    for(int i = 0; i < k; i++)
    {
        labels[i] = -2;
        sCount[i] = nLinhas/k;
        grupos[i].nomePontos = malloc(sizeof(char **) * nLinhas/k);
        grupos[i].qtdPontos = -1;
    }

    for(int i = 0; i < nLinhas; i++)
    {
        int grupo = pontos[i].pai;
        printf("O GRUPO NA STRUCT É %d\n", pontos[i].pai);
        if(grupo == -1)
        {
            printf("O GRUPO NA STRUCT ERA -1");
            printf(" Trocando para %d\n", i);
            grupo = i;
        }
        printf("O GRUPO EHHHHHHH %d\n", grupo);
        int labelIdx = binarySearch(labels, 0, latest_label_idx+1, grupo);
        for(int i = 0; i < k; i++)
        {
            if(labels[i] == grupo)
            {
                labelIdx = i;
                break;
            }
            if(labels[i] == -2)
            {
                labels[i] = grupo;
                labelIdx = i;
                break;
            }
        }
        // if(labelIdx == -1)
        // {
        //     printf("O label era -1\n");
        //     latest_label_idx++;
        //     labelIdx = latest_label_idx;
        //     labels[latest_label_idx] = grupo;
        // }

        printf("O idx do grupo é %d\n", labelIdx);
        grupos[labelIdx].qtdPontos++;
        if(grupos[labelIdx].qtdPontos > sCount[labelIdx] - 1)
        {
            printf("Estou precisando dar um realloc\n");
            sCount[labelIdx] = sCount[labelIdx]*2;
            printf("ENDEREOC DO INFERNO DO PONTEIRO ANTES: %p\n", grupos[labelIdx].nomePontos);
            printf("INFERNO DO CARALHO DE ESPAÇOS %d\n", sCount[labelIdx]);
            grupos[labelIdx].nomePontos = 
                (char **)realloc(
                    grupos[labelIdx].nomePontos, 
                    (sizeof(char **) * sCount[labelIdx])
                    );
            printf("ENDEREOC DO INFERNO DO PONTEIRO DEPOIS: %p\n", grupos[labelIdx].nomePontos);
        }
        printf("Vou atribuir o ponto %s na posição [%d,%d]\n", pontos[i].name, labelIdx, grupos[labelIdx].qtdPontos);

        grupos[labelIdx].nomePontos[grupos[labelIdx].qtdPontos] = pontos[i].name;
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
    char *pElemGrupo1 = ((Grupo *)grupo1)->nomePontos[0];
    char *pElemGrupo2 = ((Grupo *)grupo2)->nomePontos[0];
    printf("ESTOU COMPARANDO OS PONTOS %s e %s\n", pElemGrupo1, pElemGrupo2);
    return(strcmp(pElemGrupo1, pElemGrupo2));
}

void escreveArquivo(Ponto *pontos, int k, int nLinhas, char *nomeArquivo)
{
    Grupo zap[k];

    inicializaMatrizGruposPontos(zap, pontos, nLinhas, k);
    FILE *fp = fopen(nomeArquivo, "w+");
    for(int i = 0; i < k; i++)
    {
        qsort(zap[i].nomePontos, zap[i].qtdPontos+1, sizeof(char*), &compPontos);
    }
    qsort(zap, k, sizeof(Grupo), &compGrupos);
     for(int i = 0; i < k; i++)
    {
        printf("O grupo é %d\n", i);
        for(int j = 0; j <= zap[i].qtdPontos; j++)
        {
            printf("O PONTO é %s\n", zap[i].nomePontos[j]);
            fprintf(fp, "%s,", zap[i].nomePontos[j]);
        }
        fputc('\n', fp);
    }
    fclose(fp);

    for(int i = 0; i < k; i++)
    {
        free(zap[i].nomePontos);
    }
}