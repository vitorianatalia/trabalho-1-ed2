#include "File.h"
#include "Review.h"
#include "Analytics.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <chrono>

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
        outputFile << "Linha - " << i + 1 << endl;
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

    srand(time(0));

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open file" << endl;
        exit(1);
    }
    inputFile.seekg(0, std::ios::end);
    long int tam = (inputFile.tellg() / sizeof(Review));

    int n;
    cout << "Digite 10 para a saida no console ou 100 para a saida em arquivo .txt: ";
    cin >> n;

    if (n == 10) // saida em console
    {
        vector<Review> randomReview;
        Review review2;
        for (int i = 0; i < 10; i++)
        {
            long int result = 1 + (rand() % (tam - 1));
            long int pos = (result - 1) * sizeof(Review);
            cout << result << endl;
            inputFile.seekg(pos);
            inputFile.read(reinterpret_cast<char *>(&review2), sizeof(Review));
            randomReview.push_back(review2);
        }
        printConsole(&randomReview);
    }
    else if (n == 100) // saida em texto
    {
        vector<Review> randomReview;
        Review review2;
        for (int i = 0; i < 100; i++)
        {
            long int result = 1 + (rand() % (tam - 1));
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

    srand(time(0));

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open file" << endl;
        exit(1);
    }
    inputFile.seekg(0, std::ios::end);
    long int tam = (inputFile.tellg() / sizeof(Review));

    vector<int> heapReview;

    Review review2;

    for (int i = 0; i < n; i++)
    {
        long int result = 1 + (rand() % (tam - 1));
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

    if (l <= n && heapReview2[l] > heapReview2[largest])
        largest = l;

    if (r <= n && heapReview2[r] > heapReview2[largest])
        largest = r;

    if (largest != i)
    {
        swap(heapReview2[i], heapReview2[largest]);

        maxHeapify(&heapReview2, n, largest);
    }

    heapSort(&heapReview2, n);
}

void File::heapSort(vector<int> *heapReview, int n)
{
    vector<int> heapReview3 = *heapReview;

    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(&heapReview3, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(heapReview3[0], heapReview3[i]);

        maxHeapify(&heapReview3, i, 0);
    }

    for (int i = 0; i < heapReview3.size(); i++)
    {
        cout << heapReview3[i] << endl;
    }
}

void File::countingsort(vector<Review> *reviews, Analytics *analytics)
{
    long largest = reviews->at(0).getUpvotes();
    long int n = reviews->size();
    cout << "tamanho: " << n << endl;
    for (int i = 1; i < n; i++)
    {
        if (largest < reviews->at(i).getUpvotes()) {
            largest = reviews->at(i).getUpvotes();
            analytics->addComparisons();
        }
    }

    int tam = largest + 1;
    int count[tam];
    Review ordenados[n];

    int i;
    cout << "For 1" << endl;
    for (i = 0; i <= largest; i++)
    {
        count[i] = 0;
    }
    cout << "For 2" << endl;
    for (i = 0; i < n; i++)
    {
        count[reviews->at(i).getUpvotes()]++;
    }
    cout << "For 3" << endl;
    for (i = 1; i <= largest; i++)
    {
        count[i] += count[i - 1];
    }
    cout << "For 4" << endl;
    for (i = 0; i < n; i++)
    {
        analytics->addSwaps();
        ordenados[count[reviews->at(i).getUpvotes()] - 1] = reviews->at(i);
        count[reviews->at(i).getUpvotes()]--;
    }
    cout << "For 5" << endl;
    int j = n - 1;
    for (i = 0; i < n; i++)
    {
        analytics->addSwaps();
        (*reviews)[i] = ordenados[j];
        j--;
    }
    writeTxt(reviews);
}

void File::quicksort(Review *reviews, int left, int right, Analytics *analytics)
{
    int i = left;
    int j = right;
    Review pivot = reviews[(left + right) / 2];

    while (i <= j)
    {
        analytics->addComparisons();
        while (reviews[i].getUpvotes() < pivot.getUpvotes())
        {
            i++;
        }

        analytics->addComparisons();
        while (reviews[j].getUpvotes() > pivot.getUpvotes())
        {
            j--;
        }

        if (i <= j)
        {
            Review temp = reviews[i];
            reviews[i] = reviews[j];
            reviews[j] = temp;
            i++;
            j--;
            analytics->addSwaps();
        }
    }
    if (left < j)
    {
        quicksort(reviews, left, j, analytics);
    }
    if (i < right)
    {
        quicksort(reviews, i, right, analytics);
    }
}

void File::generateVector(long int n, int m, int algorithm)
{
    ifstream inputFile("tiktok_app_reviews.bin", ios::in | ios::binary);
    ofstream outputFile("results.txt", std::ofstream::out | std::ofstream::app);

    srand(time(0));

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open file" << endl;
        exit(1);
    }

    Analytics analytics;
    inputFile.seekg(0, std::ios::end);
    long int tam = (inputFile.tellg() / sizeof(Review));
    vector<Review> v;
    Review review2;

    for (int i = 0; i < n; i++)
    {
        long int result = 1 + (rand() % (tam - 1));
        long int pos = result * sizeof(Review);
        inputFile.seekg(pos);
        inputFile.read(reinterpret_cast<char *>(&review2), sizeof(Review));
        v.push_back(review2);
    }

    int avgComparisons = 0;
    int avgSwaps = 0;
    double avgTime = 0;
    int originalM = m;

    while (m > 0)
    {
        auto start = chrono::high_resolution_clock::now();
        switch (algorithm)
        {
        case 1:
            geraVetor(n);
            break;
        case 2:
            outputFile << endl;
            outputFile << "CountingSort"
                       << "\n"
                       << endl;
            countingsort(&v, &analytics);
            break;
        case 3:
            outputFile << endl;
            outputFile << "QuickSort"
                       << "\n"
                       << endl;
            quicksort(v.data(), 0, v.size() - 1, &analytics);

            break;

        default:
            cout << "Nenhum algoritmo selecionado" << endl;
            break;
        }

        auto stop = chrono::high_resolution_clock::now();

        chrono::duration<double, std::milli> ms_double = stop - start;

        outputFile << originalM - m + 1 << " Execucao" << endl;
        outputFile << "Comparacoes: " << analytics.getComparisons() << endl;
        outputFile << "Trocas: " << analytics.getSwaps() << endl;
        outputFile << "Tempo de execucao: " << ms_double.count() << "ms" << endl;

        avgComparisons += analytics.getComparisons();
        avgSwaps += analytics.getSwaps();
        avgTime += ms_double.count();

        m--;
        analytics.clear();
    }

    outputFile << endl;
    outputFile << "Media de comparacoes: " << avgComparisons / originalM << endl;
    outputFile << "Media de trocas: " << avgSwaps / originalM << endl;
    outputFile << "Media de tempo de execucao: " << avgTime / originalM << "ms" << endl;

    outputFile.close();
}