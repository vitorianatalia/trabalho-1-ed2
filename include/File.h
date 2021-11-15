#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include "string.h"
#include "vector"
#include "Review.h"

using namespace std;

class File
{
public:
    void readFile(vector<Review> *reviewList, string fileName);
    void writeTxt(vector<Review> *reviewList);
    void writeBin(vector<Review> *reviewList);
    void readBinary(vector<Review> *reviewList);
    void acessaRegistro(int n);
    // void testeImportacao(vector<Review>* reviewList);
    // void menu(int input);
};

#endif