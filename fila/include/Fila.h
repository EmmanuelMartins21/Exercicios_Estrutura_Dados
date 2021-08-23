#ifndef FILA_H
#define FILA_H
#include <iostream>
#include "No.h"

using namespace std;

class Fila
{
    public:
        Fila();
        virtual ~Fila();
        void entra(int val);
        void sai();
        void imprime();
        int consultaInicio();
        bool vazia();

    private:
        No *c;
        No *f;
};

#endif // FILA_H
