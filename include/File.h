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
    void generateVector(long int n, int m, int algorithm);
    void heapSort(Review heapReview[], long int len, Analytics *analytics);
    void heapify(Review heapReview[], long int len, long int i, Analytics *analytics);
    void countingsort(vector<Review> *reviews, Analytics *analytics);
    void quicksort(Review *reviews, int left, int right, Analytics *analytics);
    void versionCount(vector<Review> *review);
};

#endif