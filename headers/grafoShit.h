#ifndef _GRAFOSHIT_h_
#define _GRAFOSHIT_h_

#include "ponto.h"
#include <stdlib.h>


typedef struct grafo
{
    int nLinhas;
    int nArestas;
    Aresta *arestas;
}Grafo;


Grafo* criaGrafo(int nLinhas, int nArestas, Aresta* arestas);

/*
 * find
 * IN:	 *pontos - Lista de pontos
 *        i - Índice de um ponto
 * OUT:	  Pai absoluto do índice passado
 * POST: Faz compreensão do caminho, apontando todos para o pai
 */
int find(Ponto *pontos, int i);

/*
 * find
 * IN:	 *pontos - Lista de pontos
 *        xroot -  Raiz de um ponto
 *        yroot -  Raiz de outro ponto
 * OUT:	 -
 * POST: Une as "árvores", tornando a de menor rank para a de maior
 */
void uniao(Ponto *pontos, int xroot, int yroot);

/*
 * fazMst
 * IN:	 *pontos - Lista de pontos
 *       *arestas -  Lista de arestas
 *        nLinhas -  Número de linhas lidas no arquivo
 *        nArestas - Número de arestas
 *        k - Número de grupos a serem criados 
 * OUT:	 -
 * POST: Monta árvore MST com exceção das k-1 maiores arestas.
 */
void fazMst(Ponto *pontos, Aresta *arestas, int nLinhas, int nArestas, int k);

#endif