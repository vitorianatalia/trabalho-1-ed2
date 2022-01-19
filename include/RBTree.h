#pragma once
#ifndef RBTree_H_INCLUDED
#define RBTree_H_INCLUDED

#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

static const bool RED = 0;
static const bool BLACK = 1;

struct Node
{
    string data;
    long int position;
    bool color;
    Node *left, *right, *parent;


    // Constructor
    Node(string data)
    {
        this->data = data;
        left = right = parent = NULL;
        this->color = RED;
    }
};

class RBTree
{
private:
    Node *root;

public:
    RBTree() { root = NULL; };
    ~RBTree() { delete root;};
    void insert(string &data, long int n, Analytics *analytics);
    Node *auxInsert(Node *root, Node *pt, Analytics *analytics);
    void fixRules(Node *&, Node *&);
    void rotateLeft(Node *&, Node *&);
    void rotateRight(Node *&, Node *&);
    void printTree();
    void printHelper(Node *root, string indent, bool last);
    Node *search(string searchKey, Analytics *analytics)
    {
        return searchAux(this->root, searchKey, analytics);
    }
    Node *searchAux(Node *n,string searchKey, Analytics *analytics)
    {
      if (n == NULL || searchKey == n->data) {
			return n;
		}
		if (searchKey < n->data) {
			return searchAux(n->left, searchKey, analytics);
		} 
		return searchAux(n->right, searchKey, analytics);
    }
};


void RBTree::insert(string &data, long int n, Analytics *analytics)
{
    Node *pt = new Node(data);
    pt->position=n;
    root = auxInsert(root, pt, analytics);
    fixRules(root, pt);
    delete pt;
}

Node *RBTree::auxInsert(Node *root, Node *pt, Analytics *analytics)
{
    if (root == NULL)
        analytics->addComparisons();
        return pt;
    if (pt->data < root->data)
    {
        root->left = auxInsert(root->left, pt, analytics);
        root->left->parent = root;
    }
    else if (pt->data > root->data)
    {
        root->right = auxInsert(root->right, pt, analytics);
        root->right->parent = root;
    }
    analytics->addComparisons();
    return root;
}

void RBTree::fixRules(Node *&root, Node *&pt)
{
    Node *parent_pt = NULL;
    Node *grand_parent_pt = NULL;
    while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED))
    {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;
        /// case a parent of pt is left child of grand parent of pt
        if (parent_pt == grand_parent_pt->left)
        {
            Node *uncle_pt = grand_parent_pt->right;
            //case 1 the uncle of pt is also red only recoloring required
            if (uncle_pt != NULL && uncle_pt->color == RED)
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else
            {
                //case 2 pt is right child of its parent left rotation required
                if (pt == parent_pt->right)
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                //case 3 pt is left child of its parent right rotation required
                rotateRight(root, grand_parent_pt);
                bool aux;
                aux = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = aux;
                pt = parent_pt;
            }
        }
        //case b parent of pt is grand child of grand parent of pt
        else
        {
            Node *uncle_pt = grand_parent_pt->left;
            //case 1 the uncle of pt is also red only recoloring required
            if ((uncle_pt != NULL) && (uncle_pt->color == RED))
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else
            {
                //case 2 pt is left child of its parent right rotation required
                if (pt == parent_pt->left)
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                //case 3 pt is right child of its parent left rotation required
                rotateLeft(root, grand_parent_pt);
                bool aux;
                aux = parent_pt->color;
                parent_pt->color = grand_parent_pt->color;
                grand_parent_pt->color = aux;
                pt = parent_pt;
            }
        }
    }
    root->color = BLACK;
}

void RBTree::rotateLeft(Node *&root, Node *&pt)
{
    Node *pt_right = pt->right;
    pt->right = pt_right->left;
    if (pt->right != NULL)
    {
        pt->right->parent = pt;
    }
    pt_right->parent = pt->parent;
    if (pt->parent == NULL)
    {
        root = pt_right;
    }
    else if (pt == pt->parent->left)
    {
        pt->parent->left = pt_right;
    }
    else
    {
        pt->parent->right = pt_right;
    }
    pt_right->left = pt;
    pt->parent = pt_right;
}

void RBTree::rotateRight(Node *&root, Node *&pt)
{
    Node *pt_left = pt->left;
    pt->left = pt_left->right;
    if (pt->left != NULL)
    {
        pt->left->parent = pt;
    }
    pt_left->parent = pt->parent;
    if (pt->parent == NULL)
    {
        root = pt_left;
    }
    else if (pt == pt->parent->left)
    {
        pt->parent->left = pt_left;
    }
    else
    {
        pt->parent->right = pt_left;
    }
    pt_left->right = pt;
    pt->parent = pt_left;
}

void RBTree::printTree()
{
    if (root)
    {
        printHelper(this->root, "", true);
    }
}

void RBTree::printHelper(Node *root, string indent, bool last)
{
    if (root != NULL)
    {
        cout << indent;
        if (last)
        {
            cout << "R----";
            indent += "   ";
        }
        else
        {
            cout << "L----";
            indent += "|  ";
        }
        string sColor = root->color ? "BLACK" : "RED";
        cout << root->data << "(" << sColor << ")" << endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
}



#endif