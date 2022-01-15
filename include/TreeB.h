/*#ifndef TREEB_H_INCLUDED
#define TREEB_H_INCLUDED

#include <iostream>
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

    void insert(int k)
    {
        if (root == NULL)
        {

            root = new NoB(minDegree, true);
            root->key[0] = k;
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
                if (node->key[0] < k)
                    i++;
                
                node->children[i]->insertNonFull(k);

                root = node;
            }
            else
            {
                root->insertNonFull(k);
            }
        }
    }

    void printTree()
    {
        if (root != NULL)
            root->printNode();
    }
};

#endif*/