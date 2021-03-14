#ifndef _list_h_
#define _list_h_

typedef struct ponto 
{
	char *name;			// Pointer to data held by list node
	double *components;	// Pointer to next element in list
}Ponto;

typedef struct aresta
{
	Ponto *pontoA;
	Ponto *pontoB;
	double distAB;

}Aresta;



void atribuipIDX(Ponto *pontoI, int i, void *arg);
void alocaColunas(Ponto *pontoI, int nLinhas, int nColunas);
int arestaComp(const void *aresta1, const void *aresta2);
void liberaPontos(Ponto *pontos, int dimensaoL);

#endif