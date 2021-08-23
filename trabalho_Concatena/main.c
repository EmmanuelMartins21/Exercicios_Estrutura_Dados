#include <stdio.h>
#include <stdlib.h>

//estrutura da celula
typedef struct TipoCelula
{
    int info;
    struct TipoCelula *proximo;

} TipoCelula;

//Struct para guardar o início da lista
typedef struct
{
    int quantidade;
    TipoCelula *primeiro;
} TipoLista;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//cria uma lista vazia

TipoLista* criaLista()
{
    TipoLista *nova = malloc(sizeof(TipoLista));
    nova->primeiro = NULL;
    nova->quantidade = 0;
    return nova;
}

TipoCelula* criaCelula(int valor)
{
    TipoCelula *nova = malloc(sizeof(TipoCelula));
    nova->info = valor;
    nova->proximo = NULL;
    return nova;
}

TipoLista *concatena(TipoLista *lista1, TipoLista *lista2)
{
	TipoLista* p; /* vari�vel auxiliar para percorrer a lista */

	if (lista1 != NULL)
	{
		do
		{
			p = lista1;
			lista1 = lista1->primeiro;

		}while(lista1->primeiro->proximo != NULL);

		p->primeiro = lista2;
	}
}

void inserir(TipoLista *lista, int valor, int posicao)
{
    TipoCelula *novaCelula = criaCelula(valor);

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
            printf("Posição fora dos limites!\n");
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
            printf(" %d ", auxiliar->info);
            auxiliar = auxiliar->proximo;
        }
        printf("\n");
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int main()
{

    //criando o cabeçalho e células
    TipoLista *lista1 = criaLista();
    TipoLista *lista2 = criaLista();
    TipoLista *listaConcat = criaLista();

    //encadeando colocando sempre no final
    inserir(lista1,1,0);
    inserir(lista1,2,1);
    inserir(lista1,3,2);
    inserir(lista1,4,3);
    inserir(lista1,5,4);

    inserir(lista2,6,0);
    inserir(lista2,7,1);
    inserir(lista2,8,2);
    inserir(lista2,9,3);
    inserir(lista2,10,4);

    imprime(lista1);
    printf("tamanho da lista: %d\n", lista1->quantidade);

    imprime(lista2);
    printf("tamanho da lista: %d\n", lista2->quantidade);

    printf("\nA lista concatenada:\n");
    concatena(lista1, lista2);
    imprime(lista1);
    return 0;
}
