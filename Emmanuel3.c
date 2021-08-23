#include<stdio.h>
#include<stdlib.h>

int main()
{
    int vet[6] = {0,1,2,3,4,5};
    int par=0 , impar = 0;

    for(int i =0; i<6; i++)
    {
        if(vet[i]%2 == 0)
        {
            printf("Pares: %d \n", vet[i]);

            par+= vet[i];

        }
    }

     for(int i =0; i<6; i++)
     {
        if(vet[i]%2 != 0)
        {
            printf("Impar: %d \n", vet[i]);

            impar++ ;

        }
     }

    printf("Soma dos pares:%d\n", par);
    printf("Quantidade de impares: %d\n", impar);

    return 0;

}
