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

    pontos_pointer = fopen(nome, "r");
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
        perror("Problema na leitura das linhas");
        exit(3);
    }
    free(line);
    return linhas;
}


int main(int argc, char**argv)
{
    if(argc != 4)
    {
        printf("Número bizarro de argumentos de entrada\n");
        exit(1);
    }
    char *arqEntrada = argv[1];
    int k = atoi(argv[2]);
    char *arqSaida = argv[3];


    int linhas = pegaDimensoesL(arqEntrada);
    int colunas = pegaDimensoesC(arqEntrada);
    Ponto *pontos = leEntrada(arqEntrada, linhas, colunas);
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

    int delimitador = linhas - 1;
    Aresta* movimentoSemTerra = fazMst(ufVec, arestas, linhas, nArestas, k);
    free(arestas);
    int k_group_size_act[k];
    for(int i = 0; i < k; i++)
    {
        k_group_size_act[i] = 0;
    }
    int k_group_size_alct[k];
    for(int i = 0; i < k; i++)
    {
        k_group_size_alct[i] = 10;
    }
    char ***kgroup = malloc(sizeof(char**) * k);
    for(int i = 0; i < k; i++)
    {
        kgroup[i] = malloc(sizeof(char **) * 10);
    }
    
    for(int i = 0; i < linhas; i++)
    {
        int grupoPonto = -2;
        if(ufVec[i].pai != -1)
        {
            grupoPonto = ufVec[i].pai;
        }    
        else
        {
            grupoPonto = i;
        }

        k_group_size_act[grupoPonto]++;
        if(k_group_size_act[grupoPonto] > k_group_size_alct[grupoPonto])
        {
            kgroup[grupoPonto] = realloc(kgroup[grupoPonto], k_group_size_alct[grupoPonto] + 10);
            k_group_size_alct[grupoPonto] += 10;
        }
        kgroup[grupoPonto][k_group_size_act[grupoPonto]] = pontos[i].name;
        printf("O grupo é %d\n", grupoPonto);
        printf("A quantidade de elementos nesse grupo é %d\n", k_group_size_act[grupoPonto]);
        printf("O ponto %s pertence ao grupo %d\n", kgroup[grupoPonto][k_group_size_act[grupoPonto]], ufVec[i].pai);
    }


    for(int i = 0; i < k; i++)
    {
        kgroup[i] = realloc(kgroup[i], k_group_size_act[i]);
    }
    
    for(int i = 0; i < k; i++)
    {
        printf("grupo %d\n", i);
        for(int j = 0; j < k_group_size_act[i]; j++)
        {
            printf("ponto: %s\n", kgroup[i][j]);
        }
    }

    
    liberaPontos(pontos, linhas);
    free(ufVec);
    free(movimentoSemTerra);
}