#include <stdio.h>
#include <stdlib.h>

float media(float nota[5])
{
    float med=0;


    for(int i=0;i<5;i++)
    {
        med= med+nota[i];
    }

return med/5;
}

int Aprovados(float aprv[5])
{

    int ap=0, rp=0;
    for (int i=0; i< 5; i++)
    {
        if (aprv[i]>=60){
           return ap++;
        }
        else
           return  rp++;
    }
}

int main()
{

   float Notas[5]={100.0,40.8,62.0,79.9,60.7};
   float x=0;
    int A=0;

  x = media( Notas);
  A=Aprovados( Notas);

   printf(" A media dos alunos eh:%f",x);
   printf(" Os alunos aprovados sao %d",A);



//printf("Hello world!\n");
    return 0;
}
