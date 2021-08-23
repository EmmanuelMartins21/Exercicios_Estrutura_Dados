
#include<stdio.h>

int comp (int *A, int *B, int *C)
{
    int a1,b1,c1;
    if((*A < *B) && (*A<*C))
    {
        a1 = *A;
        if(*B<*C)
        {
            b1=*B;
            c1=*C;
        }
        else
        {
            b1=*C;
            c1=*B;
        }
    }

    if((*B < *A) && (*B<*C))
    {
        a1 = *B;
        if(*A<*C)
        {
            b1=*A;
            c1=*C;
        }
        else
        {
            b1=*C;
            c1=*A;
        }
    }
    if((*C < *A) && (*C<*B))
    {
        a1 = *C;
        if(*A<*B)
        {
            b1=*A;
            c1=*B;
        }
        else
        {
            b1=*B;
            c1=*A;
        }

    }

    *A=a1;
    *B=b1;
    *C=c1;
return 0;
}

int main(){
int a=20,b=12,c=18;

comp(&a,&b,&c);

     printf("A ordem e:%d %d %d", a,b,c);

}
