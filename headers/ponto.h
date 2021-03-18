#ifndef _PONTO_H_
#define _PONTO_H_

typedef struct ponto 
{
	char *name;			
	double *components;
	int pai;
	int rank;
}Ponto;

typedef struct aresta
{
	int pontoA;
	int pontoB;
	double distAB;

}Aresta;

typedef struct grupo
{
	char **nomePontos;
	int qtdPontos;

}Grupo;


/*
 * atribuipIDX
 * IN:	 *pontoI - Lista de pontos
 * 		  *arg ponteiro para dado lido do arquivo
 * 		  i índice da coluna em que arg foi lido
 * OUT:	 -
 * POST: Atribui arg a ponto. Nome se i for 0 e 
 * 			componente no índice i-1 caso contrário.
 */
void atribuipIDX(Ponto *pontoI, int i, void *arg);

/*
 * alocaColunas
 * IN:	 *pontoI - Lista de pontos
 * 		  nLinhas Número de linhas lidas no arquivo
 * 		  nColunas Número de colunas lidas no arquivo
 * OUT:	 -
 * POST: Aloca memória para o vetor de componentes dos pontos.
 */
void alocaColunas(Ponto *pontoI, int nLinhas, int nColunas);

/*
 * arestaComp
 * IN:	 *aresta1 - Ponteiro para aresta.
 * 		 *aresta2 Ponteiro para aresta.
 * OUT:	 1 se aresta1 > aresta2
 * 		 0 se aresta1 == aresta2
 * 		-1 se aresta1 < aresta2
 * POST: -
 */
int arestaComp(const void *aresta1, const void *aresta2);

/*
 * liberaPontos
 * IN:	 *pontos - Lista de pontos
 * OUT:	 -
 * POST: Libera toda a memória usada pelos pontos
 */
void liberaPontos(Ponto *pontos, int dimensaoL);

/*
 * escreveArquivo
 * IN:	 *pontos - Lista de pontos.
 * 		 *nomeArquivo - Caminho e nome para arquivo de saída.
 * 		  nLinhas - Número de linhas lidas no arquivo de entrada.
 * 		  k - Número de grupos.
 * OUT:	 -
 * POST: Arquivo no caminho especificado.
 */
void escreveArquivo(Ponto *pontos, int k, int nLinhas, char *nomeArquivo);


#endif