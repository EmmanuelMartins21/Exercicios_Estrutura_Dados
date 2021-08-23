#include "ABD.h"

LIST* criaLista(){
    LIST *l = malloc(sizeof(LIST));
    l->inicio = l->fim = NULL;
    return l;
}

bool listIsEmpty(LIST *l){
	return l->inicio == NULL;
}

TREE* createTree(){
    return NULL;
}

bool treeIsEmpty(TREE* t){
    return t == NULL;
}

void insereLista(LIST *list, TREE *t){
	ELEMENT *e = malloc(sizeof(ELEMENT));
	e->tree = t;
	e->prox = NULL;
	
	if(listIsEmpty(list)){
		list->inicio = list->fim = e;
	}else{
		list->fim->prox = e;
		list->fim = e;
	}
}

TREE* lerNo(FILE *f){
	char texto[100], leitor;
	bool check=false;
	int i=0, pointer = ftell(f);
	
	fscanf(f, "%s", texto);
	if(strcmp("}", texto)==0){
		fseek(f, -1, SEEK_CUR);
		return;
	}
	
	TREE *aux = malloc(sizeof(TREE));
	aux->dir = aux->esq = NULL;
	aux->id = malloc(sizeof(char)*strlen(texto));
	strcpy(aux->id, texto);
	
	do{
		fscanf(f, "%c", &leitor);
		
		if(leitor == ';')
			break;
		else if(leitor=='"'){
			check = !check;
			continue;
		}else if(leitor=='-'){
			fseek(f, pointer, SEEK_SET);
			return NULL;
		}
		
		if(check){
			texto[i] = leitor;
			i++;
		}
	}while(true);
	texto[i] = '\0';
	
	aux->label = malloc(sizeof(char)*strlen(texto));
	strcpy(aux->label, texto);
	
	return aux;
}

POINTER* lerPonteiro(FILE *f){
	char texto[100], leitor;
	bool check=false;
	int i=0;
	POINTER *aux = malloc(sizeof(POINTER));
	
	for(;i<2;i++){
		fscanf(f, "%s", texto);
		if(strcmp("}", texto)==0){
			fseek(f, -1, SEEK_CUR);
			return NULL;
		}
		aux->id[i] = malloc(sizeof(char)*strlen(texto));
		strcpy(aux->id[i], texto);
		fseek(f, 3, SEEK_CUR);
	}
	i=0;
	do{
		fscanf(f, "%c", &leitor);
		
		if(leitor == ';')
			break;
		else if(leitor=='"'){
			check = !check;
			continue;
		}
		
		if(check){
			texto[i] = leitor;
			i++;
		}
	}while(true);
	
	aux->direcao = texto[0];
	
	return aux;
}

void montarArvore(LIST *l, POINTER *p){
	ELEMENT *e = l->inicio;
	ELEMENT *e1 = l->inicio;
	
	if(p){
		while(strcmp(p->id[0], e->tree->id)!=0)
			e = e->prox;

		while(strcmp(p->id[1], e1->tree->id)!=0)
			e1 = e1->prox;
		
		if(p->direcao == 's')
			e->tree->esq = e1->tree;
		else if (p->direcao == 'n')
			e->tree->dir = e1->tree;
	}else
		return;
	
}

void imprimeA(TREE *t){
	if(!treeIsEmpty(t)){
		printf("%s %s\n", t->id, t->label);
		imprimeA(t->esq);
		imprimeA(t->dir);
	}
}

TREE* fillTree(LIST *list)
{
	int a;
	char leitor;
	FILE *file;
	POINTER *p;
	TREE *aux;
	bool check=false;
	
	file = fopen("lanator.dot", "r");
	
	if(file){
		do{
			a = fscanf(file, "%c", &leitor);
			if(leitor=='{' || leitor=='}'){
				check = !check;
			}else if(check){
				aux = lerNo(file);
				if(aux)
					insereLista(list, aux);
				else
					break;
			}
		}while(leitor != '}' && a!=-1);
		
		if(a==-1){
			fclose(file);
			printf("Erro crítico!");
			getch();
			exit(0);
		}
			
		while(true){
			p = lerPonteiro(file);
			if(p){
				montarArvore(list, p);
				free(p);
				p=NULL;
			}else
				break;
		}
		fclose(file);
		return list->inicio->tree;
	}else{
		printf("Erro ao abrir arquivo!");
	}
	fclose(file);
	return NULL;
}

bool manager(TREE *t)
{
	char op;
	LIST *l = criaLista();
	
	if(!treeIsEmpty(t))
	{
		// free t
		// free l
	}
		
	t = fillTree(l);
	imprimeA(t);
	//executar(t);
	
	printf("\n\t\t\t\tDeseja executar novamente? (S/N)");
	do op = getch(); while(op!='s' && op!='S' && op!='n' && op!='N');
	
	if(op=='s' || op=='S')
		return true;
	else
		return false;
}

bool menu(TREE *t)
{	
	char op;
	
	printf("\n\n\n\n");
	printf("\t\t\t\t=========== LANATOR ===========\n");
	printf("\t\t\t\t=====  1 - Iniciar        =====\n");
	printf("\t\t\t\t=====  2 - Sair           =====\n");
	printf("\t\t\t\t===============================\n\n");
	
	op = getch();
	
	switch(op){
		case '1':
			system("cls");
			return manager(t);
		break;
		
		case '2': case 27:
			return false;
		break;
}


	}
}


