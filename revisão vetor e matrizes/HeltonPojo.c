#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct no{
    char Pergunta[30];
    char nome[3];
    struct no *sim, *nao;
}Raiz;

void imprime(Raiz* r){
	if(r != NULL){
		printf("%s\n", r->Pergunta);
		imprime(r->sim);
		imprime(r->nao);
	}
}

int busca(Raiz* r, char obj[]){
    if(r == NULL){
        return 0;
    }else if(!strcmp(r->Pergunta, obj)){
    	return 1;
	}else if(busca(r->sim, obj)){
		return 1;
	}else if(busca(r->nao, obj)){
		return 1;
	}
}

void limpa(Raiz* r){
	if(r != NULL){
        if(r->sim != NULL && r->nao != NULL){
        	free(r);
        	return;
		}
		limpa(r->sim);
        limpa(r->nao);
    }
}

Raiz* criaRaiz(Raiz* r, char obj[], Raiz* p){
	r = malloc(sizeof(Raiz));
	if(busca(p, obj)){
		printf("\nObjeto já existente, insira um novo: ");
		fflush(stdin);
		gets(obj);
		fflush(stdin);
	}
	sprintf(r->Pergunta,"%s", obj);
	r->sim = NULL;
	r->nao = NULL;
	return r;
}

Raiz* le(Raiz* r){
	FILE *arq;
	int vf = 0, vf2 = 0, tam = 0, i = 0, j = 0, cont = 0, a, apont1, apont2;;
	char texto[500], obj[30], nome[3], nome2[3];

	arq = fopen("Akinator.dot", "r");
	while(!feof(arq)){
		fscanf(arq, "%c", &texto[tam]);
		tam++;
	}
	fclose(arq);

	while(texto[i] != '/'){
		if(texto[i] == ';'){
			cont++;
		}
		i++;
	}
	Raiz *p[cont];
	cont = 0;
	i = 0;

	while(i < tam){
		if(texto[i] == '{'){
			vf = 1;
		}else if(texto[i] == '/'){
			vf = 2;
		}else if(texto[i] == '}'){
			vf = 0;
		}

		if(vf == 1){
			if(texto[i] == 'z'){
				vf2 = 1;
				j = 0;
			}else if(texto[i - 1] == '"' && texto[i] != ']'){
				vf2 = 2;
				j = 0;
			}

			if(vf2 == 1){
				nome[j] = texto[i];
				j++;
				if(texto[i + 2] == '['){
					vf2 = -1;
				}
			}else if(vf2 == 2){
				obj[j] = texto[i];
				j++;
				if(texto[i + 1] == '"'){
					vf2 = -2;
				}
			}

			if(vf2 == -2){
				p[cont] = criaRaiz(p[cont], obj, r);
				for(a = 0; a < 30; a++){
					obj[a] = '\0';
				}
				sprintf(p[cont]->nome,"%s", nome);
				for(a = 0; a < 3; a++){
					nome[a] = '\0';
					nome2[a] = '\0';
				}
				vf2 = 0;
				cont++;
			}

		}else if(vf == 2){
			if(texto[i + 3] == '-'){
				vf2 = 3;
				j = 0;
			}else if(texto[i - 2] == '>'){
				vf2 = 4;
				j = 0;
			}else if(texto[i - 1] == '"' && texto[i] != ']'){
				vf2 = 5;
				j = 0;
			}

			if(vf2 == 3){
				nome[j] = texto[i];
				j++;
				if(texto[i + 2] == '-'){
					vf2 = -3;
				}
			}else if(vf2 == 4){
				nome2[j] = texto[i];
				j++;
				if(texto[i + 2] == '['){
					vf2 = -4;
				}
			}else if(vf2 == 5){
				obj[j] = texto[i];
				j++;
				if(texto[i + 1] == '"'){
					vf2 = -5;
				}
			}else if(texto[i] == ';'){
				for(a = 0; a < cont; a++){
					if(!strcmp(p[a]->nome, nome)){
						apont1 = a;
					}else if(!strcmp(p[a]->nome, nome2)){
						apont2 = a;
					}
				}
				if(!strcmp(obj, "sim")){
					p[apont1]->sim = p[apont2];
				}else{
					p[apont1]->nao = p[apont2];
				}
				for(a = 0; a < 30; a++){
					obj[a] = '\0';
				}
				for(a = 0; a < 3; a++){
					nome[a] = '\0';
					nome2[a] = '\0';
				}
			}
		}
		i++;
	}
	r = p[0];
	return r;
}

Raiz* percorre(Raiz* p, int* cont){
	int i = 0;
	char obj[30], rep, sair;
	Raiz *r = p, *t = p;
	while(sair != 'n'){
		i = 0;
		r = t;
		while(i == 0 && sair != 'W'){
			if(r == NULL){
				printf("Não foi possível encontrar um objeto, informe um objeto: ");
				fflush(stdin);
				gets(obj);
				fflush(stdin);
				r = criaRaiz(r, obj, t);
	        	t = r;
	        	i = 1;
			}else if(r->sim == NULL && r->nao == NULL){
				printf("É %s?(s/n): ", r->Pergunta);
				fflush(stdin);
				scanf("%c", &rep);
				fflush(stdin);

				if(rep == 'n'){
					printf("Então qual é?: ");
					fflush(stdin);
					gets(obj);
					fflush(stdin);
					Raiz *aux = criaRaiz(aux, obj, t);
					printf("Informe uma questão para a qual a resposta sim significa '%s' e a não significa '%s': ", aux->Pergunta, r->Pergunta);
					fflush(stdin);
					gets(obj);
					fflush(stdin);

					if((*cont) == 0){
						Raiz *aux2 = criaRaiz(aux2, r->Pergunta, NULL);
					}else{
						Raiz *aux2 = criaRaiz(aux2, r->Pergunta, t);
					}
	        		sprintf(r->Pergunta,"%s",obj);

					r->sim = aux;
					//r->nao = aux2;

					if((*cont) == 0){
						t = r;
					}
					(*cont)++;
				}
				i = 1;
			}else{
				printf("%s(s/n): ", r->Pergunta);
				fflush(stdin);
				scanf("%c", &rep);
				fflush(stdin);

				if(rep == 's'){
					r = r->sim;
				}else if(rep == 'n'){
					r = r->nao;
				}else{
					r = r->sim;
				}
			}
		}
		printf("Deseja executar novamente?(s/n): ");
		fflush(stdin);
		scanf("%c", &sair);
		fflush(stdin);

		if(sair != 's' && sair != 'n'){
			system("cls");
			printf("ERRO\nESCOLHA NOVAMENTE\n");
			system("color 04");
			sair = 'W';
			system("pause");
			system("color 07");
			system("cls");
		}
	}
	p = t;
	return p;
}

void preenche(Raiz* r,FILE* file, int* cont){
	if(r != NULL){
		(*cont)++;
		sprintf(r->nome, "z%i", (*cont));
        fprintf(file, "\t%s [label=\"%s\"];\n", r->nome, r->Pergunta);
        preenche(r->sim, file, cont);
		preenche(r->nao, file, cont);
    }
}

void preencheponts(Raiz* r,FILE* file){
	if(r->sim != NULL && r->nao != NULL){
		fprintf(file, "\t%s -> %s [label=\"sim\"];\n", r->nome, r->sim->nome);
		fprintf(file, "\t%s -> %s [label=\"nao\"];\n", r->nome, r->nao->nome);
		preencheponts(r->sim, file);
		preencheponts(r->nao, file);
	}
}

void salva(Raiz* r){
	FILE *arq;
	Raiz *corre = r;
	int *end, cot = 0;

	end = &cot;
	arq = fopen("Akinator.dot", "w");
	fprintf(arq, "digraph graphname\n{\n");

	preenche(corre, arq, end);
	fprintf(arq, "\n\t//ponteiros\n");
	corre = r;
	preencheponts(corre, arq);

	fprintf(arq, "\n}");
	fclose(arq);
}

void run(){
	Raiz *r = NULL;
	char c;
	int j = 0;
	while(j == 0){
		system("cls");
		printf("Bem-vindo ao Mini akinator\nEscolha o Modo No Menu E se Divirta\n");
		printf("1-Crie sua árvore de Desição do zero\n");
		printf("2-Jogue com uma árvore de desição pré-definida\n");
		printf("3-Sair\nOpção: ");

		fflush(stdin);
		scanf("%c", &c);
		fflush(stdin);
		system("cls");

		switch(c){
			limpa(r);
			int i;
			case '1':{
				i = 0;
				r = percorre(r, &i);
				salva(r);
				break;
			}
			case '2':{
				i = 1;
				r = le(r);
				r = percorre(r, &i);
				salva(r);
				break;
			}
			case '3':{
				j = 1;
				break;
			}
			default:{
				break;
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
    run();
}
