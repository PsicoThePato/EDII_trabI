#ifndef _MATHSHIT_h_
#define _MATHSHIT_h_


#include <math.h>
#include "../headers/ponto.h"

/*
 * euclidDist
 * IN:	 *vetor1 - Componentes de um ponto
 * 		 *vetor2 - Componentes de um ponto
 * 		  dimensao - Dimensão dos pontos
 * OUT:	 Distância entre os pontos
 * POST: -
 */
double euclidDist(double *vetor1, double *vetor2, int dimensao);

/*
 * euclidDist
 * IN:	 *pontos - Lista de pontos
 * 		  dimensaoL - Número de linhas lidas do arquivo
 * 		  dimensaoC - Número de colunas lidas em uma linha do arquivo.
 *        nArestas - Número de arestas a serem criadas.
 * OUT:	 Lista de arestas com peso
 * POST: -
 */
Aresta* wtArestas(Ponto* pontos, int dimensaoL, int dimensaoC, int nArestas);



#endif