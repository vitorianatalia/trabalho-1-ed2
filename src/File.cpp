#include "File.h"
#include "Review.h"
#include <fstream>

#include <iostream>
#include <vector>
#include <cstdlib> 
#include <time.h>
#include <algorithm>

using namespace std;

void File::readFile(vector<Review> *reviewList, string filename)
{
    ifstream arq(filename.c_str(), ios::in);
    Review review;

    if (!arq.is_open())
    {
        cout << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    string line;
    line.clear();

    while (!arq.eof())
    {
        getline(arq, line, ',');
        review.setReview_id(line);
        line.clear();

        char c = arq.get();
        if (c == '\"')
        {
            getline(arq, line, '\"');
            review.setReview_text(line);
            line.clear();

            string comma;
            getline(arq, comma, ',');
        }
        else
        {
            getline(arq, line, ',');
            line.insert(0, 1, c);
            review.setReview_text(line);
            line.clear();
        }

        getline(arq, line, ',');
        review.setUpvotes(atoi(line.c_str()));
        line.clear();

        getline(arq, line, ',');
        review.setAppVersion(line);
        line.clear();

        getline(arq, line, '\n');
        review.setPostedDate(line);
        line.clear();

        reviewList->push_back(review);
    }
    return;
}

void File::writeTxt(vector<Review> *reviewList)
{
    ofstream outputFile("tiktok_app_reviews.txt", std::ofstream::out | std::ofstream::trunc);

    for (int i = 0; i < reviewList->size(); i++)
    {
        outputFile << "Linha - " << i+1 << endl;
        outputFile << "ID: " << reviewList->at(i).getReview_id() << endl;
        outputFile << "Texto: " << reviewList->at(i).getReview_text() << endl;
        outputFile << "Votos: " << reviewList->at(i).getUpvotes() << endl;
        outputFile << "Versão: " << reviewList->at(i).getAppVersion() << endl;
        outputFile << "Data: " << reviewList->at(i).getPostedDate() << endl;

        outputFile << "\n";
        outputFile << "\n";
    }

    outputFile.close();
}

void File::writeBin(vector<Review> *reviewList)
{
    ofstream outputFile("tiktok_app_reviews.bin", ios::out | ios::trunc | ios::binary);

    for (int i = 0; i < reviewList->size(); i++)
    {
        outputFile.write(reinterpret_cast<char *>(&reviewList->at(i)), sizeof(Review));
    }

    outputFile.close();
}

void File::readBinary(vector<Review> *reviewList)
{
    ifstream inputFile("tiktok_app_reviews.bin", ios::in | ios::binary);

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open file" << endl;
        exit(1);
    }

    Review review;

    while (inputFile.read(reinterpret_cast<char *>(&review), sizeof(Review)))
    {
        reviewList->push_back(review);
    }

    for (int i = 0; i < reviewList->size(); i++)
    {
        cout << "versao:" << reviewList->at(i).getAppVersion() << endl;
        cout << "data:" << reviewList->at(i).getPostedDate() << endl;
        cout << "id:" << reviewList->at(i).getReview_id() << endl;
        cout << "texto:" << reviewList->at(i).getReview_text() << endl;
        cout << "likes:" << reviewList->at(i).getUpvotes() << endl;
        cout << endl;
    }
    inputFile.close();
}

void File::printConsole(vector<Review> *reviewList)
{
    for (int i = 0; i < reviewList->size(); i++)
    {
        cout << "ID:" << reviewList->at(i).getReview_id() << endl;
        cout << "Texto:" << reviewList->at(i).getReview_text() << endl;
        cout << "Votos:" << reviewList->at(i).getUpvotes() << endl;
        cout << "Versao:" << reviewList->at(i).getAppVersion() << endl;
        cout << "Data:" << reviewList->at(i).getPostedDate() << endl;
        cout << endl;
    }
}


void File::acessaRegistro(long int n)
{
    ifstream inputFile("tiktok_app_reviews.bin", ios::in | ios::binary);

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open file" << endl;
        exit(1);
    }

    Review review;

    long int pos = (n - 1) * sizeof(Review);
    inputFile.seekg(pos);
    inputFile.read(reinterpret_cast<char *>(&review), sizeof(Review));

    cout << endl;
    cout << "ID: " << review.getReview_id() << endl;
    cout << "Texto: " << review.getReview_text() << endl;
    cout << "Votos: " << review.getUpvotes() << endl;
    cout << "Versao: " << review.getAppVersion() << endl;
    cout << "Data: " << review.getPostedDate() << endl;
    cout << endl;
}

void File::testeImportacao()
{
    ifstream inputFile("tiktok_app_reviews.bin", ios::in | ios::binary);

    srand (time(0));
    
    if (!inputFile.is_open())
    {
        cout << "Error: Could not open file" << endl;
        exit(1);
    }
    inputFile.seekg(0, std::ios::end);
    long int tam = (inputFile.tellg()/sizeof(Review));

    int n;
    cout << "Digite 10 para a saida no console ou 100 para a saida em arquivo .txt: ";
    cin >> n;
    
    if (n == 10) //saida em console
    {
        vector<Review> randomReview;
        Review review2;
        for (int i=0; i<10; i++) {
            long int result = 1 + (rand() % (tam-1));
            long int pos = (result - 1) * sizeof(Review);
            cout << result << endl;
            inputFile.seekg(pos);
            inputFile.read(reinterpret_cast<char *>(&review2), sizeof(Review));
            randomReview.push_back(review2);
        }
        printConsole(&randomReview);
    }
    else if (n == 100) //saida em texto
    {
        vector<Review> randomReview;
        Review review2;
        for (int i=0; i<100; i++) {
            long int result = 1 + (rand() % (tam-1));
            long int pos = (result - 1) * sizeof(Review);
            inputFile.seekg(pos);
            inputFile.read(reinterpret_cast<char *>(&review2), sizeof(Review));
            randomReview.push_back(review2);
        }
        writeTxt(&randomReview);
    }
}

void File::geraVetor(long int n)
{
    ifstream inputFile("tiktok_app_reviews.bin", ios::in | ios::binary);

    srand (time(0));
    
    if (!inputFile.is_open())
    {
        cout << "Error: Could not open file" << endl;
        exit(1);
    }
    inputFile.seekg(0, std::ios::end);
    long int tam = (inputFile.tellg()/sizeof(Review));

    vector<int> heapReview;
    
    Review review2;

    for (int i=0; i<n; i++) {
        long int result = 1 + (rand() % (tam-1));
        long int pos = (result - 1) * sizeof(Review);
        inputFile.seekg(pos);
        inputFile.read(reinterpret_cast<char *>(&review2), sizeof(Review));
        heapReview.push_back(review2.getUpvotes());
    }

    int a = heapReview.size();
    int i = 0;

    maxHeapify(&heapReview, a, i);
}

void File::maxHeapify(vector<int> *heapReview, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    vector<int> heapReview2 = *heapReview;
 
    if(l <= n && heapReview2[l] > heapReview2[largest])
        largest = l;
 
    if(r <= n && heapReview2[r] > heapReview2[largest])
        largest = r;
 
    if(largest != i) {
        swap(heapReview2[i], heapReview2[largest]);
 
        maxHeapify(&heapReview2, n, largest);
    }

    heapSort(&heapReview2, n);
}

void File::heapSort(vector<int> *heapReview, int n)
{
    vector<int> heapReview3 = *heapReview;

    for(int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(&heapReview3, n, i);
 
    for(int i = n - 1; i > 0; i--) {
        swap(heapReview3[0], heapReview3[i]);
 
        maxHeapify(&heapReview3, i, 0);
    }

    for (int i = 0; i < heapReview3.size(); i++)
    {
        cout << heapReview3[i] << endl;
    }
}

void File::generateVector(long int n)
{
    ifstream inputFile("tiktok_app_reviews.bin", ios::in | ios::binary);

    srand (time(0));
    
    if (!inputFile.is_open())
    {
        cout << "Error: Could not open file" << endl;
        exit(1);
    }
    inputFile.seekg(0, std::ios::end);
    long int tam = (inputFile.tellg()/sizeof(Review));

    vector<Review> v;
    
    Review review2;

    for (int i=0; i<n; i++) {
        long int result = 1 + (rand() % (tam-1));
        long int pos = (result - 1) * sizeof(Review);
        inputFile.seekg(pos);
        inputFile.read(reinterpret_cast<char *>(&review2), sizeof(Review));
        v.push_back(review2);
    }

    int a = v.size();
    int i = 0;

    
    countingsort(&v, n);
}

void countingsort(vector<Review> *reviews, const long n)
{
    cout << "Upvotes: " << reviews[0].at(0).getUpvotes() << endl;
    // long i;
    // long largest = reviews[0].getUpvotes();
    // long *tmp = new long[n];

    // for(i = 1; i< n; i++)
    // {
    //     if(largest < reviews[i])
    //     largest  = reviews[i];
    // }

    // unsigned long *count = new unsigned long[largest+1];

    // for(i = 0; i <= largest; i++)
    // {
    //     count[i] = 0;
    // }

    // for(i = 0; i < n; i++)
    // {
    //     count[reviews[i]]++;
    // }

    // for(i = 1; i <= largest; i++)
    // {
    //     count[i] = count[i-1] + count[i];
    // }

    // for(i = n-1; i >= 0; i++)
    // {
    //     tmp[count[reviews[i]] - 1] = reviews[i];
    //     count[reviews[i]]--;
    // }

    // for(i = 0; i <= n; i++)
    // {
    //     reviews[i] = tmp[i];
    // }
}