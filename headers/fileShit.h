#ifndef _FILESHIT_H_
#define _FILESHIT_H_

#include "ponto.h"


/*
 * leEntrada
 * IN:	 *nome - String com caminho para o arquivo de entradas
 * 		 nLinhas - Número de linhas do arquivo
 * 		 nColunas - Número de colunas do arquivo
 * OUT:	 Lista de pontos inicializados
 * POST: -
 */
Ponto* leEntrada(char* nome, int nLinhas, int nColunas);

/*
 * pegaDimensoesL
 * IN:	 *nome - String com caminho para o arquivo de entradas
 * OUT:	 Número de linhas do arquivo
 * POST: -
 */
int pegaDimensoesL(char *nome);

/*
 * pegaDimensoesC
 * IN:	 *nome - String com caminho para o arquivo de entradas
 * OUT:	 Número de colunas do arquivo
 * POST: -
 */
int pegaDimensoesC(char *nome);

#endif