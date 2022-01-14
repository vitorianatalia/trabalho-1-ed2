#ifndef RBTree_H_INCLUDED
#define RBTree_H_INCLUDED

#include "RBNode.h"
#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

class RBTree
{
private:
    Node *root;

public:
    RBTree() { root = NULL; };
    void insert(string &data);
    void fixRules(Node *&, Node *&);
    void rotateLeft(Node *&, Node *&);
    void rotateRight(Node *&, Node *&);
};

Node *auxInsert(Node *root, Node *pt)
{
    if (root == NULL)
        return pt;
    if (pt->getData() < root->getData())
    {
        root->setLeft(auxInsert(root->getLeft(), pt));
        root->getLeft()->setParent(root);
    }
    else if (pt->getData() < root->getData())
    {
        root->setRight(auxInsert(root->getRight(), pt));
        root->getRight()->setParent(root);
    }
    return root;
}

void RBTree::fixRules(Node *&root, Node *&pt)
{
    Node *parent_pt = NULL;
    Node *grand_parent_pt = NULL;
    while ((pt != root) && (pt->getColor() != 1) && (pt->getParent()->getColor() == 0))
    {
        parent_pt = pt->getParent();
        grand_parent_pt = pt->getParent()->getParent();
        /// case a parent of pt is left child of grand parent of pt
        if (parent_pt == grand_parent_pt->getLeft())
        {
            Node *uncle_pt = grand_parent_pt->getRight();
            //case 1 the uncle of pt is also red only recoloring required
            if (uncle_pt != NULL && uncle_pt->getColor() == 0)
            {
                grand_parent_pt->setColor(0);
                parent_pt->setColor(1);
                uncle_pt->setColor(1);
                pt = grand_parent_pt;
            }
            else
            {
                //case 2 pt is right child of its parent left rotation required
                if (pt == parent_pt->getRight())
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->getParent();
                }
                //case 3 pt is left child of its parent right rotation required
                rotateRight(root, grand_parent_pt);
                bool aux;
                aux = parent_pt->getColor();
                parent_pt->setColor(grand_parent_pt->getColor());
                grand_parent_pt->setColor(aux);
                pt = parent_pt;
            }
        }
        //case b parent of pt is grand child of grand parent of pt
        else
        {
            Node *uncle_pt = grand_parent_pt->getLeft();
            //case 1 the uncle of pt is also red only recoloring required
            if ((uncle_pt != NULL) && (uncle_pt->getColor() == 0))
            {
                grand_parent_pt->setColor(0);
                parent_pt->setColor(1);
                uncle_pt->setColor(1);
                pt = grand_parent_pt;
            }
            else
            {
                //case 2 pt is left child of its parent right rotation required
                if (pt == parent_pt->getLeft())
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->getParent();
                }
                //case 3 pt is right child of its parent left rotation required
                rotateLeft(root, grand_parent_pt);
                bool aux;
                aux = parent_pt->getColor();
                parent_pt->setColor(grand_parent_pt->getColor());
                grand_parent_pt->setColor(aux);
                pt = parent_pt;
            }
        }
    }
    root->setColor(1);
}

void RBTree::rotateLeft(Node *&root, Node *&pt)
{
    Node *pt_right = pt->getRight();
    pt->setRight(pt_right->getLeft());
    if (pt->getRight() != NULL)
    {
        pt->getRight()->setParent(pt);
    }
    pt_right->setParent(pt->getParent());
    if (pt->getParent() == NULL)
    {
        root = pt_right;
    }
    else if (pt == pt->getParent()->getLeft())
    {
        pt->getParent()->setLeft(pt_right);
    }
    else
    {
        pt->getParent()->setRight(pt_right);
    }
    pt_right->setLeft(pt);
    pt->setParent(pt_right);
}

void RBTree::rotateRight(Node *&root, Node *&pt)
{
    Node *pt_left = pt->getLeft();
    pt->setLeft(pt_left->getRight());
    if (pt->getLeft() != NULL)
    {
        pt->getLeft()->setParent(pt);
    }
    pt_left->setParent(pt->getParent());
    if (pt->getParent() == NULL)
    {
        root = pt_left;
    }
    else if (pt == pt->getParent()->getLeft())
    {
        pt->getParent()->setLeft(pt_left);
    }
    else
    {
        pt->getParent()->setRight(pt_left);
    }
    pt_left->setRight(pt);
    pt->setParent(pt_left);
}

void RBTree::insert(string &data)
{
    Node *pt = new Node(data);
    root = auxInsert(root, pt);
    fixRules(root, pt);
}
#endif