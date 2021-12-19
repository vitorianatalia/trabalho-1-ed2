#include "../include/Hash.h"
#include <list>
#include <iostream>

using namespace std;

Hash::Hash(int b)
{
    this->balde = b;
    table = new list<int>[balde];
}

void Hash::insert(string key)
{
    int index = hashfunction(key);
    table[index].push_back(key);
}

void Hash::displayhash()
{
    for (int i = 0; i < balde; i++)
    {
        cout << i;
        for (auto x : table[i])
            cout << " --> " << x;
        cout << endl;
    }
}
