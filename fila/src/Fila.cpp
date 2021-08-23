#include "Fila.h"

Fila::Fila()
{
    c = NULL;
    f=NULL;
}

Fila::~Fila()
{
    No *p = c;
    while(p!=NULL)
    {
        No *t = p->getProx();
        delete p;
        p = t;
    }
    f = NULL;
}

void Fila::entra(int val)
{
    No *p = new No();
    p->setInfo(val);
    p->setProx(NULL);
    if(f==NULL)
        c = p;
    else
        f->setProx(p);
    f = p;
}

void Fila::sai()
{
    No *p;
    if(c==NULL)
        cout<<"Lista vazia"<<endl;
    else
    {
        p = c;
        c = p->getProx();
        if(c==NULL)
            f = NULL;
        delete p;
    }
}

void Fila::imprime()
{
    if(c!=NULL)
    {
        cout<<c->getInfo()<<endl;

    }
    else
        cout<<"Fila vazia"<<endl;
}

int Fila::consultaInicio()
{
    if(c!=NULL)
    {
        return c->getInfo();
    }
    else
        cout<<"Fila vazia"<<endl;
}

bool Fila::vazia()
{
    if(c==NULL)
        return true;
    else
        return false;
}
