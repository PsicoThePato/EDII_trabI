#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/ponto.h"
#include "../headers/grafoShit.h"

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

    }

    else
    {
        pontoI->components[i-1] = atof(*(char **)arg);
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

    int grupo = 0;
    for(int i = 0; i < nLinhas; i++)
    {

        grupo = find(pontos, i);
        int labelIdx = -5;
    
        for(int j = 0; j < k; j++)
        {
            if(labels[j] == grupo)
            {
                labelIdx = j;
                break;
            }
            if(labels[j] == -2)
            {
                labels[j] = grupo;
                labelIdx = j;
                break;
            }
            if(j == k-1)
                exit(3);
        }

        grupos[labelIdx].qtdPontos++;
        
        if(grupos[labelIdx].qtdPontos > sCount[labelIdx] - 1) //realloc espaços*2 caso precise.
        {
            sCount[labelIdx] = sCount[labelIdx]*2;
            grupos[labelIdx].nomePontos = 
                (char **)realloc(
                    grupos[labelIdx].nomePontos, 
                    (sizeof(char **) * sCount[labelIdx])
                    );
        }
        
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
    return(strcmp(pElemGrupo1, pElemGrupo2));
}

void escreveArquivo(Ponto *pontos, int k, int nLinhas, char *nomeArquivo)
{
    Grupo *zap = (Grupo *)malloc(sizeof(Grupo) * k);

    inicializaMatrizGruposPontos(zap, pontos, nLinhas, k);
    FILE *fp = fopen(nomeArquivo, "w+");
    
    for(int i = 0; i < k; i++)
    {
        qsort(zap[i].nomePontos, zap[i].qtdPontos+1, sizeof(char*), &compPontos);
    }
    qsort(zap, k, sizeof(Grupo), &compGrupos);
    
    for(int i = 0; i < k; i++)
    {
        for(int j = 0; j <= zap[i].qtdPontos; j++)
        {
            fprintf(fp, "%s", zap[i].nomePontos[j]);
            if(j != zap[i].qtdPontos)
            {
                fprintf(fp, ",");
            }
        }
        fputc('\n', fp);
    }
    fclose(fp);

    for(int i = 0; i < k; i++)
    {
        free(zap[i].nomePontos);
    }
    free(zap);
}