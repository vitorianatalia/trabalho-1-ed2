#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include "string.h"
#include "vector"
#include "Review.h"
#include "Analytics.h"

using namespace std;

class File
{
public:
    File() {}

    ~File() {}

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
    void generateVector(long int n, int m, int algorithm);
    void countingsort(vector<Review> *reviews);
    void quicksort(Review *reviews, int left, int right, Analytics *analytics);
};

#endif