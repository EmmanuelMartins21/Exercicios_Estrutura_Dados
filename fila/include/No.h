#ifndef NO_H
#define NO_H
#include <iostream>

using namespace std;

class No
{
    public:
        No();
        virtual ~No();
        No *getProx();
        void setProx(No *p);
        int getInfo();
        void setInfo(int val);

    private:
        No *proximo;
        int info;
};

#endif // NO_H
