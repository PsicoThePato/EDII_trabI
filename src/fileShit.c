#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../headers/ponto.h"

Ponto* leEntrada(char* nome, int nLinhas, int nColunas)
{
    FILE *pontos_pointer;
    Ponto *pontos = malloc(sizeof(Ponto) *nLinhas);
    alocaColunas(pontos, nLinhas, nColunas);

    pontos_pointer = fopen(nome, "r");
    if(!pontos_pointer)
    {
        perror("Fopen retornou ponteiro nulo na abertura do aqruivo!\n");
        exit(1);
    }
    char *line;
    size_t len = 0;
    ssize_t nRead;
    char *line_token;
    int iterAuxL = 0;
    while((nRead = getline(&line, &len, pontos_pointer)) != -1)
    {
        if (iterAuxL >= nLinhas)
        {
            perror("Número de linhas passado inferior ao número de linhas no arquivo");
            exit(4);
        }

        line_token = strtok(line, ",");
        int iterAuxC = 0;
        
        while(line_token != NULL)
        {
            atribuipIDX(&(pontos[iterAuxL]), iterAuxC, &line_token);
            line_token = strtok(NULL, ",");
            iterAuxC++;
        }
        pontos[iterAuxL].pai = -1;
        pontos[iterAuxL].rank = 0;
        iterAuxL++;
    }
    free(line);
    fclose(pontos_pointer);
    return pontos;
}


int pegaDimensoesC(char *nome)
{
    FILE *pontos_pointer;
    pontos_pointer = fopen(nome, "r");
    if(pontos_pointer == NULL)
    {
        perror("N abri\n");
        exit(2);
    }
    
    char *line;
    size_t len = 0;
    
    getline(&line, &len, pontos_pointer);
    char *line_token = strtok(line, ",");
    
    int dimensoes = -1; //Jacques Vallee reference?
    while(line_token != NULL)
    {
        dimensoes++;
        line_token = strtok(NULL, ",");
    }

    fclose(pontos_pointer);
    free(line);
    return dimensoes;

}


int pegaDimensoesL(char *nome)
{
    FILE *pontos_pointer;
    pontos_pointer = fopen(nome, "r");
    if(pontos_pointer == NULL)
    {
        perror("N abri\n");
        exit(2);
    }
    
    char *line;
    size_t len = 0;
    ssize_t nRead;
    
    int linhas = 0;
    while((nRead = getline(&line, &len, pontos_pointer)) != -1)
    {
        linhas++;
    }
    fclose(pontos_pointer);

    if(!linhas)
    {
        perror("Problema na leitura das linhas\n");
        exit(3);
    }
    free(line);
    return linhas;
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
