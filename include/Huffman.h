#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#include "Analytics.h"
#include <string>
#include <iostream>

using namespace std;

class Huffman
{
private:
    string txt;

public:
    Huffman(){};
    ~Huffman(){};

    void buildHuffmanTree(string txt, int n, Analytics *analytics, int cycle);
};

#endif // HUFFMAN_H_INCLUDED