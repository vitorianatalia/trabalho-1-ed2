#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include "string.h"
#include "vector"
#include "Review.h"
#include "Hash.h"
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
    void countingsort(Review *reviews, long int n, Analytics *analytics);
    void quicksort(Review *reviews, int left, int right, Analytics *analytics);
    void testVector(int n, int m, int algorithm);
    void runHash(long int n, int verificador);
    void countingSortInt(vector<int> *v, int n);
    void arvores(int i);
    void treeBCaseFunction(ifstream &inputFile, ofstream &outputFile, long int b, long int tam, int order, int currentCicle, int maxRepeat, long int comparacaoI, float comparacaoB, float tempoI, float tempoB, int searchId, string idS);
    void treeRBCaseFunction(ifstream &inputFile, ofstream &outputFile, long int b, long int tam, int currentCicle, int maxRepeat, string idS);
    void generateTxtHuffman(int n);
};

#endif