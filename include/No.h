#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

#include <iostream>

using namespace std;

class No
{
private:
    string info;
    No *prox;

public:
    No(){};
    ~No(){};

    void setInfo(string info)
    {
        this->info = info;
    };

    void setProx(No *prox)
    {
        this->prox = prox;
    };

    string getInfo()
    {
        return info;
    };

    No *getProx()
    {
        return prox;
    };
};

#endif