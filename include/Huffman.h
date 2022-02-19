#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

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

    void buildHuffmanTree(string txt, int n);
};

#endif // HUFFMAN_H_INCLUDED