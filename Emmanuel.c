#include<stdio.h>
void receber(int A, int B, int *P)
{
    *P = A*B;


}


int main()
{
    int A=5,B=3,C;

    receber(A,B,&C);

    printf("C = %d", C);

    return 0;
}
