#include <Hash.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

Hash::Hash(long long int size)
{
    this->size = size;
    linkedList = new ListaEncadeada *[size];
    for (int i = 0; i < size; i++)
    {
        linkedList[i] = new ListaEncadeada();
    }
}

Hash::~Hash()
{
    for (int i = 0; i < size; i++)
    {
        delete linkedList[i];
    }
    delete[] linkedList;
}

int Hash::hashfunction(string x)
{
    int hash = 0;
    for (int i = 0; i < x.length(); i++)
    {
        hash = hash + x[i];
    }
    return hash % size;
}

void Hash::insert(string x)
{
    int hash = hashfunction(x);
    linkedList[hash]->insert(x);
}

No *Hash::search(string x)
{
    int hash = hashfunction(x);
    return linkedList[hash]->search(x);
}

void Hash::printLinkedList(string x)
{
    int hash = hashfunction(x);
    linkedList[hash]->print();
}

bool Hash::infoAlreadyExists(string x){
    int hash = hashfunction(x);
    bool result = linkedList[hash]->infoAlreadyExists(x);

    return result;
}