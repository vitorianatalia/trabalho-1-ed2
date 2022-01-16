#ifndef KEYB_H_INCLUDED
#define KEYB_H_INCLUDED

#include <iostream>
#include "TreeB.h"

using namespace std;

class KeyB
{
private:
    string id;
    long int position;

public:
    KeyB(){};
   
    ~KeyB(){};

    void setId(string id)
    {
        this->id = id;
    };

    string getId()
    {
        return id;
    };

    void setPosition(long int position)
    {
        this->position = position;
    }

    int getPosition()
    {
        return position;
    }
};

#endif