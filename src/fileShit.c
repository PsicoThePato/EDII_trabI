#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../headers/ponto.h"
#include "../headers/dbg.h"
#include "../headers/mathShit.h"
#include "../headers/grafoShit.h"

Ponto* leEntrada(char* nome, int nLinhas, int nColunas)
{
    FILE *pontos_pointer;
    Ponto *pontos = malloc(sizeof(Ponto) *nLinhas);
    alocaColunas(pontos, nLinhas, nColunas);

    pontos_pointer = fopen("in/1.txt", "r");
    check(pontos_pointer, "DEU RUIM NA ABERTURA DO ARQUIVO")
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

        //printf("%s\n", line);
        line_token = strtok(line, ",");
        int iterAuxC = 0;
        while(line_token != NULL)
        {
            //char *teste = strdup(line_token);
            atribuipIDX(&(pontos[iterAuxL]), iterAuxC, &line_token);
            //printf("%s\n", line_token);
            line_token = strtok(NULL, ",");
            iterAuxC++;
        }
        iterAuxL++;
    }
    free(line);
    fclose(pontos_pointer);
    return pontos;

error:
    exit(1);
}


int pegaDimensoesC(char *nome)
{
    FILE *pontos_pointer;
    pontos_pointer = fopen("in/1.txt", "r");
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
    pontos_pointer = fopen("in/1.txt", "r");
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
        perror("Problema na leitura das linhas");
        exit(3);
    }
    free(line);
    return linhas;
}


int main()
{
    int linhas = pegaDimensoesL("nome");
    int colunas = pegaDimensoesC("nome");

    Ponto *pontos = leEntrada("nome", linhas, colunas);
    for(int i = 0; i < linhas; i ++)
    {
        //printf("%s ", pontos[i].name);
        for(int j = 0; j < colunas; j++)
        {
            //printf("%lf\n", pontos[i].components[j]);
        }
        //printf("\n");
    }

    int nArestas = (linhas * (linhas - 1))/2;
    Aresta *arestas = wtArestas(pontos, linhas, colunas, nArestas);
    qsort(arestas, nArestas, sizeof(Aresta), &arestaComp);
    //Grafo *grafo = criaGrafo(linhas, nArestas, arestas);
    Subset *ufVec = malloc(sizeof(Subset) * linhas);
    for(int i = 0; i < linhas; i++)
    {
        ufVec[i].pai = -1;
        ufVec[i].rank = 0;
    }

    int k = 3;
    int delimitador = linhas - k;
    Aresta* movimentoSemTerra = fazMst(ufVec, arestas, linhas, nArestas, k);
    for(int i = 0; i < delimitador; i++)
    {
        printf("############");
        printf("PONTO A: %d\n", movimentoSemTerra[i].pontoA);
        printf("PONTO B: %d\n", movimentoSemTerra[i].pontoB);
        printf("############");
        printf("Aresta (%s %s) \n", pontos[movimentoSemTerra[i].pontoA].name, pontos[movimentoSemTerra[i].pontoB].name);

    }
    liberaPontos(pontos, linhas);
    free(arestas);
    free(ufVec);
    free(movimentoSemTerra);
}