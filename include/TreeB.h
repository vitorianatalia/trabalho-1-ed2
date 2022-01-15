#ifndef TREEB_H_INCLUDED
#define TREEB_H_INCLUDED

#include <string.h>
#include <iostream>
#include "KeyB.h"
#include "NoB.h"

using namespace std;


class TreeB
{
private:
    NoB *root;
    int minDegree;

public:
    TreeB(int t)
    {
        root = NULL;
        minDegree = t;
    }

    void insert(KeyB no)
    {
        if (root == NULL)
        {
            root = new NoB(minDegree, true);
            root->key[0] = no;
            root->currentTotalNode = 1;
        }
        else
        {
            if (root->currentTotalNode == 2 * minDegree - 1)
            {
                NoB *node = new NoB(minDegree, false);
                node->children[0] = root;

                node->splitChild(0, root);

                int i = 0;
                if (node->key[0].getId() < no.getId())
                    i++;

                node->children[i]->insertNonFull(no);

                root = node;
            }
            else
            {
                root->insertNonFull(no);
            }
        }
    }

    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

    NoB *search(KeyB noTeste)
    {
        return (root == NULL) ? NULL : root->search(noTeste);
    }
};

#endif