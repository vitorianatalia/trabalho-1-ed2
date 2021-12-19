#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include "ListaEncadeada.h"
#include "No.h"


class Hash
{
private:
    long long int size;
    ListaEncadeada **linkedList;

public:
    Hash(long long int size);
    ~Hash();
    int hashfunction(string x);
    void insert(string x);
    No* search(string x);
    void printLinkedList(string x);
    bool infoAlreadyExists(string x);
};

#endif // HASH_H_INCLUDED