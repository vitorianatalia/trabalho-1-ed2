#ifndef TREEB_H_INCLUDED
#define TREEB_H_INCLUDED

#include <string.h>
#include <iostream>
#include "KeyB.h"
#include "NoB.h"
#include "Analytics.h"

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

    ~TreeB()
    {
        delete root;
    }

    void insert(KeyB no, Analytics *analytics)
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

                node->splitChild(0, root, analytics);
                
                int i = 0;
                if (node->key[0].getId() < no.getId()){
                    analytics->addComparisons();
                    i++;
                }

                node->children[i]->insertNonFull(no, analytics);

                root = node;
            }
            else
            {
                root->insertNonFull(no, analytics);
            }
        }
    }

    NoB *search(string searchKey, Analytics *analytics)
    {
        return (root == NULL) ? NULL : root->search(searchKey, analytics);
    }
};

#endif