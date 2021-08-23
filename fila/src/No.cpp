#include "No.h"

No::No()
{
    //ctor
}

No::~No()
{
    //dtor
}

No* No::getProx()
{
    return proximo;
}

void No::setProx(No *p)
{
    proximo = p;
}

int No::getInfo()
{
    return info;
}

void No::setInfo(int val)
{
    info = val;
}


