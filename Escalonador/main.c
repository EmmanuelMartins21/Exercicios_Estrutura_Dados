/*  Bruno Resende Arce
    Emmanuel Cosme Martins Bento
    CEFET-MG Leopoldina
    Laboratório de Estrutura de dados
    SO: Windows 10
    Code Blocks 20.03
*/

#include <stdio.h>
#include <stdlib.h>

#define QUANTA 5

//estrutura da célula
typedef struct TipoCelula
{
    int id;
    int dur_total;
    int dur_decorrida;
    float num_quantas;
    struct TipoCelula *proximo;

} TipoCelula;

//Struct para guardar o início da lista
typedef struct
{
    int quantidade;
    TipoCelula *primeiro;
} TipoLista;

//cria uma lista vazia
TipoLista* criaLista()
{
    TipoLista *nova = malloc(sizeof(TipoLista));
    nova->primeiro = NULL;
    nova->quantidade = 0;
    return nova;
}

TipoCelula* criaCelula(int id, int dur_total)
{
    TipoCelula *nova = malloc(sizeof(TipoCelula));
    nova->id = id;
    nova->dur_total = dur_total;
    nova->dur_decorrida = 0;
    nova->num_quantas = 0;
    nova->proximo = NULL;
    return nova;
}

void inserir(TipoLista *lista, int id, int dur_total,int posicao)
{
    TipoCelula *novaCelula = criaCelula(id,dur_total);

    //lista vazia
    if(lista->quantidade == 0)
    {
        lista->primeiro = novaCelula;
        lista->quantidade++;
    }
    else
    {
        //inicio
        if(posicao == 0)
        {
            novaCelula->proximo = lista->primeiro;
            lista->primeiro = novaCelula;
            lista->quantidade++;

        }
        //meio
        else if(posicao > 0 && posicao < lista->quantidade)
        {
            //eu não sei qual o endereço bloco na posição desejada
            //eu tenho que varrer a lista para achar
            TipoCelula *aux = lista->primeiro;
            int pos = 0;
            //paro na celula imediatamente anterior
            while(pos < posicao - 1)
            {
                aux = aux->proximo;
                pos++;
            }

            //ajustanto ponteiros
            novaCelula->proximo = aux->proximo;
            aux->proximo = novaCelula;
            lista->quantidade++;
        }
        //final
        else if(posicao == lista->quantidade)
        {
            //eu não sei qual o endereço bloco final
            //eu tenho que varrer a lista para achar
            TipoCelula *aux = lista->primeiro;
            //paro no último elemento
            while(aux->proximo != NULL)
                aux = aux->proximo;

            //ajustanto ponteiros
            aux->proximo = novaCelula;
            lista->quantidade++;
        }
        else
        {
            printf("Posicao fora dos limites!\n");
        }
    }
}

void remover(TipoLista *lista, int posicao)
{
    TipoCelula *auxiliar, *auxiliar2;

    //lista vazia
    if(lista->quantidade == 1)
    {
        auxiliar = lista->primeiro;
        lista->primeiro = NULL;
        free(auxiliar);
        lista->quantidade--;
    }
    else if(lista->quantidade > 1)
    {
        //inicio
        if(posicao == 0)
        {
            auxiliar = lista->primeiro;
            lista->primeiro = lista->primeiro->proximo;
            free(auxiliar);
            lista->quantidade--;

        }
        //meio
        else if(posicao > 0 && posicao < lista->quantidade)
        {
            auxiliar = lista->primeiro;
            int pos = 0;

            //paro na celula imediatamente anterior à desejada
            while(pos < posicao - 1)
            {
                auxiliar = auxiliar->proximo;
                pos++;
            }

            //o elemento que quero apagar
            auxiliar2 = auxiliar->proximo;
            //o elemento seguinte ao que quero apagar
            auxiliar->proximo = auxiliar->proximo->proximo;

            free(auxiliar2);
            lista->quantidade--;

        }
        //fim
        else if(posicao == lista->quantidade)
        {

            auxiliar = lista->primeiro;
            int pos = 0;

            //paro na penulima celula
            while(pos < posicao - 2)
            {
                auxiliar = auxiliar->proximo;
                pos++;
            }

            //o elemento seguinte ao que quero apagar (último)
            free(auxiliar->proximo);
            auxiliar->proximo = NULL;
            lista->quantidade--;

        }
        else
        {

            printf("Indice fora dos limites!\n");
        }
    }
    else
    {
        printf("Lista vazia!\n");
    }
}

//imprime
void imprime(TipoLista *lista)
{
    TipoCelula *auxiliar = lista->primeiro;

    if(lista->primeiro == NULL)
    {
        printf("Lista vazia!\n");
    }
    else
    {
        while(auxiliar != NULL)
        {
            printf("id %d - duracao %d\n", auxiliar->id,auxiliar->dur_total);
            auxiliar = auxiliar->proximo;
        }
        printf("\n");
    }
}


void atualiza_quantas(TipoLista *lista)
{
    TipoCelula *auxiliar = lista->primeiro;

    if(lista->primeiro == NULL)
    {

    }
    else
    {
        while(auxiliar != NULL)
        {
            auxiliar->num_quantas = auxiliar->num_quantas + 1;
            auxiliar = auxiliar->proximo;
        }
    }
}

//imprime
TipoLista* copia(TipoLista *lista)
{
    TipoCelula *a1 = lista->primeiro;

    TipoLista * listaNova = criaLista();
    int cont = 0;

    while(a1 != NULL)
    {
        inserir(listaNova,a1->id,a1->dur_total,cont);
        a1 = a1->proximo;
        cont++;
    }

    return listaNova;
}


TipoLista* ordenar(TipoLista *lista){
	TipoCelula *aux = lista->primeiro;
	TipoCelula *aux2 = aux->proximo;
	int cont = 0;
	int flag = 0;
	while(aux!=NULL){
		if(aux->proximo!=NULL){
			if(aux->dur_total > aux->proximo->dur_total){
				remover(lista, cont);
				inserir(lista, aux->id, aux->dur_total, cont+1);
				aux = lista->primeiro;
				cont = 0;
				flag = 1;
			}
		}
		if(flag==0){
			aux = aux->proximo;
			cont++;
		}
		flag = 0;
	}
	imprime(lista);
}


void round_robin(TipoLista *lista)
{

	TipoCelula *aux = lista->primeiro;
    int pos = 0;
    float med_quantas = 0;

    printf("ROUND ROBIN\n");

    while(lista->primeiro != NULL)
    {
        if(aux->dur_decorrida < aux->dur_total)
        {
            printf("CPU PARA PROCESSO %d TOTAL %d RESTANTE %d\n", aux->id, aux->dur_total, aux->dur_total - aux->dur_decorrida);
            aux->dur_decorrida = aux->dur_decorrida  + QUANTA;
            atualiza_quantas(lista);
            aux = aux->proximo;
            pos++;

            if(aux == NULL)
            {
                aux = lista->primeiro;
                pos = 0;
                printf("\n");
            }
        }
        else
        {
            med_quantas = med_quantas + aux->num_quantas;
            aux = aux->proximo;
            remover(lista, pos);

            if(aux == NULL)
            {
                aux = lista->primeiro;
                pos = 0;
                printf("\n");
            }
        }
    }

    printf("ESCALONAMENTO FINALIZADO\n");
    printf("MEDIA DE TEMPO DE UM PROCESSO NA MEMORIA %.2f QUANTAS OU %.2f SEG.\n", med_quantas/20,med_quantas/20*QUANTA);

}

void sjf(TipoLista *lista){
	ordenar(lista);
	TipoCelula *aux = lista->primeiro;
    float med_quantas = 0;

    printf("Shortest job first\n");
        while(lista->primeiro != NULL)
		{
        	if(aux->dur_decorrida < aux->dur_total)
			{
            	printf("CPU PARA PROCESSO %d TOTAL %d RESTANTE %d\n", aux->id, aux->dur_total, aux->dur_total - aux->dur_decorrida);
            	aux->dur_decorrida = aux->dur_decorrida  + QUANTA;
            	atualiza_quantas(lista);

        	}
			else
			{
            	med_quantas = med_quantas + aux->num_quantas;
            	aux = aux->proximo;
            	remover(lista, 0);
            	printf("\n");

        	}
    	}
    	printf("ESCALONAMENTO FINALIZADO\n");
    	printf("MEDIA DE TEMPO DE UM PROCESSO NA MEMORIA %.2f QUANTAS OU %.2f SEG.\n", med_quantas/20,med_quantas/20*QUANTA);
}

void SRT(TipoLista *lista){
	TipoCelula *aux = lista->primeiro;
	TipoCelula *aux2 = lista->primeiro;
	int menorTempo;
	int cont = 0;
    int pos = 0;
    float med_quantas = 0;
    printf("Shortest remaining time\n");
    while(lista->primeiro != NULL){
    	menorTempo =50;
    	cont=0;
		aux2 = lista->primeiro;
		while(aux2!=NULL){
			if((aux2->dur_total - aux2->dur_decorrida) < menorTempo){
    			aux = aux2;
    			pos = cont;
    			menorTempo = aux2->dur_total - aux2->dur_decorrida;
			}
			cont++;
			aux2 = aux2->proximo;
		}
        printf("CPU PARA PROCESSO %d TOTAL %d RESTANTE %d\n", aux->id, aux->dur_total, aux->dur_total - aux->dur_decorrida);
        aux->dur_decorrida = aux->dur_decorrida + QUANTA;
        atualiza_quantas(lista);
		if(aux->dur_total <= aux->dur_decorrida){
			med_quantas = med_quantas + aux->num_quantas;
			remover(lista, pos);
			aux = lista->primeiro;
			pos=0;
			printf("\n");
		}
	}
	printf("ESCALONAMENTO FINALIZADO\n");
    printf("MEDIA DE TEMPO DE UM PROCESSO NA MEMORIA %.2f QUANTAS OU %.2f SEG.\n", med_quantas/20,med_quantas/20*QUANTA);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int main()
{
	int  i,opcao=20003;
    TipoLista *lista1 = criaLista();
	TipoLista *lista2;
	TipoLista *lista3;
    //gerando processos
    for(i = 0; i < 20; i++)
	{
        inserir(lista1, i+1, 1+rand()%49, i);
    }
    lista2 = copia(lista1);
    lista3 = copia(lista1);
    imprime(lista1);
    system("pause");

    do{
        system("cls");
        printf("*****ESCOLHA O ESCALONADOR*****\n");
        printf("\tDigite 1 para o Round Robin\n");
        printf("\tDigite 2 para o Shortest Job First\n");
        printf("\tDigite 3 para o Shortest Remaining Time\n");
        printf("\t Digite 0 para Sair\n");
        scanf("%d",&opcao);
        if(opcao == 1)
        {
            round_robin(lista1);
            system("pause");
        }
        else if(opcao == 2)
        {
            sjf(lista2);
            system("pause");
        }
        else if(opcao == 3)
        {
            SRT(lista3);
            system("pause");
        }
        else if(opcao == 0)
        {
            break;
        }
        else{
            printf("\nValor invalido");
            break;
        }

    }while(opcao!=0);

}
