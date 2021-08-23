#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct TREE{
	char *id;
	char *label;
	struct TREE *esq, *dir;
}TREE;

typedef struct PONTEIRO{
	char *id[2];
	char direcao;
}POINTER;

typedef struct ELEMENT{
	TREE *tree;
	struct ELEMENT *prox;
}ELEMENT;

typedef struct{
	ELEMENT *inicio, *fim;
}LIST;

void executar(TREE *t);
void copiarString(TREE *t, FILE *f);
bool menu(TREE *t);
bool manager(TREE *t);

TREE* createTree();
bool treeIsEmpty(TREE* t);
TREE* fillTree(LIST *list);

LIST* criaLista();
void insereLista(LIST *list, TREE *t);
bool listIsEmpty(LIST *l);
void imprimeA(TREE *t);
