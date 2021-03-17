#ifndef _PONTO_H_
#define _PONTO_H_

typedef struct ponto 
{
	char *name;			// Pointer to data held by list node
	double *components;	// Pointer to next element in list
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

void atribuipIDX(Ponto *pontoI, int i, void *arg);
void alocaColunas(Ponto *pontoI, int nLinhas, int nColunas);
int arestaComp(const void *aresta1, const void *aresta2);
void liberaPontos(Ponto *pontos, int dimensaoL);
int binarySearch(int *vetor, int piso, int teto, int x);
void ordenaPontos(Ponto *pontos, int k, int nLinhas);
#endif