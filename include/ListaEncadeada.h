#ifndef LISTAENCADEADA_H_INCLUDED
#define LISTAENCADEADA_H_INCLUDED
#include "No.h"

#include <iostream>

using namespace std;

class ListaEncadeada
{

private:
    No *first;

public:
    ListaEncadeada()
    {
        first = NULL;
    }

    ~ListaEncadeada()
    {
        No *aux = first;
        while (aux != NULL)
        {
            first = first->getProx();
            delete aux;
            aux = first;
        }
    }

    void insert(string info)
    {
        No *aux = new No();
        aux->setInfo(info);
        aux->setProx(first);
        first = aux;
    }

    No* search(string info)
    {
        No *aux = first;
        while (aux != NULL)
        {
            if (aux->getInfo() == info)
            {
                return aux;
            }
            aux = aux->getProx();
        }
        cout << "Nao encontrado" << endl;
        return NULL;
    }

    bool infoAlreadyExists(string info)
    {
        No *aux = first;
        while (aux != NULL)
        {
            if (aux->getInfo() == info)
            {
                return true;
            }
            aux = aux->getProx();
        }
        return false;
    }

    void print()
    {
        No *aux = first;
        while (aux != NULL)
        {
            cout << aux->getInfo() << endl;
            aux = aux->getProx();
        }
    }

    int size()
    {
        No *aux = first;
        int i = 0;
        while (aux != NULL)
        {
            i++;
            aux = aux->getProx();
        }
        return i;
    }
};

#endif
