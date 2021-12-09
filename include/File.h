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
    void acessaRegistro(long int n);
    void testeImportacao();
    void printConsole(vector<Review> *reviewList);
    void geraVetor(long int n);
    void maxHeapify(vector<int> *heapReview, int n, int i);
    void heapSort(vector<int> *heapReview, int n);
};

#endif