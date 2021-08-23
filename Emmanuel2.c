#include<stdio.h>


void retorna ( int *A, int B)
{
     *A+=B;
}



int main()
{
    int a= 5, b=6;

    retorna(&a,b);

    printf("O valor de A=%d ", a);
    printf("O valor de B =%d ",b);
}
