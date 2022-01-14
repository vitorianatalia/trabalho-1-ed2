#ifndef RBNode_H_INCLUDED
#define RBNode_H_INCLUDED

#include <iostream>
#include <string.h>

using namespace std;

class Node
{
private:
    string data;
    bool color;
    Node *parent, *right, *left;

public:
    static const bool RED = 0;
    static const bool BLACK = 1;
    Node(string data)
    {
        this->data = data;
        left = right = parent = NULL;
        this->color = RED;
    }
    void setParent(Node *parent)
    {
        this->parent = parent;
    }
    void setRight(Node *right)
    {
        this->right = right;
    }
    void setLeft(Node *left)
    {
        this->right = right;
    }
    void setColor(bool color)
    {
        this->color = color;
    }
    void setData(string data)
    {
        this->data = data;
    }
    Node *getParent()
    {
        return parent;
    }
     Node *getRight()
    {
        return right;
    }
     Node *getLeft()
    {
        return left;
    }
     bool getColor()
    {
        return color;
    }
     string getData()
    {
        return data;
    }
};

#endif