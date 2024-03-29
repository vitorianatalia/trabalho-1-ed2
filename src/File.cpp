#include "File.h"
#include "Review.h"
#include "Analytics.h"
#include "Hash.h"
#include "TreeB.h"
#include "KeyB.h"
#include "NoB.h"
#include "RBTree.h"
#include "Huffman.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <chrono>
#include <map>

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

    long int tam;
    cout << "Numero de registros a considerar: ";
    cin >> tam;
    srand(time(0));

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open file" << endl;
        exit(1);
    }
    inputFile.seekg(0, std::ios::end);

    int n;
    cout << "Digite 10 para a saida no console ou 100 para a saida em arquivo .txt: ";
    cin >> n;

    if (n == 10) // saida em console
    {
        vector<Review> randomReview;
        Review review2;
        for (int i = 0; i < tam; i++)
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
        for (int i = 0; i < tam; i++)
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

void File::heapSort(Review heapReview[], long int len, Analytics *analytics)
{
    for (long int i = len / 2 - 1; i >= 0; i--)
    {
        heapify(heapReview, len, i, analytics);
    }

    for (long int i = len - 1; i >= 0; i--)
    {
        swap(heapReview[0], heapReview[i]);
        analytics->addSwaps();
        heapify(heapReview, i, 0, analytics);
    }
}

void File::heapify(Review heapReview[], long int len, long int i, Analytics *analytics)
{
    long int max = i;
    long int l = 2 * i;
    long int r = 2 * i + 1;

    if (l < len && heapReview[l].getUpvotes() > heapReview[max].getUpvotes())
    {
        analytics->addComparisons();
        max = l;
    }

    if (r < len && heapReview[r].getUpvotes() > heapReview[max].getUpvotes())
    {
        analytics->addComparisons();
        max = r;
    }

    if (max != i)
    {
        analytics->addComparisons();
        swap(heapReview[i], heapReview[max]);
        analytics->addSwaps();
        heapify(heapReview, len, max, analytics);
    }
}

void File::countingsort(Review *reviews, long int n, Analytics *analytics)
{
    long largest = reviews[0].getUpvotes();

    for (int i = 1; i < n; i++)
    {
        if (largest < reviews[i].getUpvotes())
        {
            largest = reviews[i].getUpvotes();
        }
    }

    long int *count = new long int[largest + 1];
    Review *ordenados = new Review[n];

    int i;
    for (i = 0; i <= largest; i++)
    {
        count[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        count[reviews[i].getUpvotes()]++;
    }
    for (i = 1; i <= largest; i++)
    {
        count[i] += count[i - 1];
    }
    for (i = 0; i < n; i++)
    {
        analytics->addSwaps();
        ordenados[count[reviews[i].getUpvotes()] - 1] = reviews[i];
        count[reviews[i].getUpvotes()]--;
    }
    int j = n - 1;
    for (i = 0; i < n; i++)
    {
        analytics->addSwaps();
        reviews[i] = ordenados[j];
        j--;
    }
    delete[] ordenados;
    delete[] count;
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
    ofstream outputFile("saida.txt", std::ofstream::out | std::ofstream::app);

    srand(time(NULL));

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

    Review *vetorReviews = new Review[n];
    for (long int i = 0; i < n; i++)
    {
        vetorReviews[i] = v.at(i);
    }

    while (m > 0)
    {
        auto start = chrono::high_resolution_clock::now();
        switch (algorithm)
        {
        case 1:
            outputFile << endl;
            outputFile << "HeapSort"
                       << "\n"
                       << endl;
            heapSort(v.data(), n, &analytics);
            break;
        case 2:
            outputFile << endl;
            outputFile << "CountingSort"
                       << "\n"
                       << endl;
            countingsort(v.data(), n, &analytics);
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
    delete[] vetorReviews;
}

void File::testVector(int n, int m, int algorithm)
{
    ifstream inputFile("tiktok_app_reviews.bin", ios::in | ios::binary);
    ofstream outputFile("teste.txt", std::ofstream::out | std::ofstream::app);

    srand(time(NULL));

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

    Review *vetorReviews = new Review[n];
    for (long int i = 0; i < n; i++)
    {
        vetorReviews[i] = v.at(i);
    }

    outputFile << "Teste de Ordencao " << algorithm << " =====================" << endl;

    while (m > 0)
    {
        auto start = chrono::high_resolution_clock::now();
        switch (algorithm)
        {
        case 1:
            outputFile << endl;
            outputFile << "HeapSort"
                       << "\n"
                       << endl;
            heapSort(v.data(), n, &analytics);
            break;
        case 2:
            outputFile << endl;
            outputFile << "CountingSort"
                       << "\n"
                       << endl;
            countingsort(v.data(), n, &analytics);
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
    outputFile << "=========================================" << endl;
    outputFile << endl;

    outputFile.close();
    delete[] vetorReviews;
}

void File::countingSortInt(vector<int> *v, int n)
{
    long largest = v->at(0);

    for (int i = 1; i < n; i++)
    {
        if (largest < v->at(i))
        {
            largest = v->at(i);
        }
    }

    long int *count = new long int[largest + 1];
    int *ordenados = new int[n];

    int i;
    for (i = 0; i <= largest; i++)
    {
        count[i] = 0;
    }

    for (i = 0; i < n; i++)
    {
        count[v->at(i)]++;
    }

    for (i = 1; i <= largest; i++)
    {
        count[i] += count[i - 1];
    }

    for (i = 0; i < n; i++)
    {
        ordenados[count[v->at(i)] - 1] = v->at(i);
        count[v->at(i)]--;
    }

    int j = n - 1;
    for (i = 0; i < n; i++)
    {
        v->at(i) = ordenados[j];
        j--;
    }

    delete[] ordenados;
    delete[] count;
}

void File::runHash(long int n, int verificador)
{
    ifstream inputFile("tiktok_app_reviews.bin", ios::in | ios::binary);
    ofstream outputFile("teste.txt", std::ofstream::out | std::ofstream::app);

    srand(time(NULL));

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open file" << endl;
        exit(1);
    }

    inputFile.seekg(0, std::ios::end);
    long int tam = (inputFile.tellg() / sizeof(Review));
    Review *vetorReviews = new Review[n + 1];
    Review review2;

    for (int i = 0; i <= n; i++)
    {
        long int result = 1 + (rand() % (tam - 1));
        long int pos = result * sizeof(Review);
        inputFile.seekg(pos);
        inputFile.read(reinterpret_cast<char *>(&review2), sizeof(Review));
        vetorReviews[i] = review2;
    }

    Hash hash(n);
    map<string, int> mymap;
    map<string, int>::iterator it;
    vector<int> v;

    for (int i = 0; i <= n; i++)
    {
        if (hash.infoAlreadyExists(vetorReviews[i].getAppVersion()) == false)
        {
            hash.insert(vetorReviews[i].getAppVersion());
            mymap[vetorReviews[i].getAppVersion()] = 0;
        }
        else
        {
            it = mymap.find(vetorReviews[i].getAppVersion());
            it->second++;
        }
    }

    for (it = mymap.begin(); it != mymap.end(); it++)
    {
        int teste = it->second;
        v.push_back(teste);
    }

    for (int i = 0; i < v.size(); i++)
    {
        cout << v.at(i) << " ";
    }

    cout << endl;

    countingSortInt(&v, v.size());

    for (int i = 0; i < v.size(); i++)
    {
        cout << v.at(i) << " ";
    }

    cout << endl;

    map<string, int> myorderedmap;

    cout << "VERSOES ORDENADAS PELA FREQUENCIA ==========" << endl;
    outputFile << "VERSOES ORDENADAS PELA FREQUENCIA ==========" << endl;

    for (int aux = 0; aux < v.size(); aux++)
    {
        for (it = mymap.begin(); it != mymap.end(); it++)
        {
            if (it->second == v.at(aux))
            {
                myorderedmap.insert(pair<string, int>(it->first, it->second));
                mymap.erase(it);
                cout << it->first << " ==> " << it->second << endl;
                if (verificador)
                {
                    outputFile << it->first << " ==> " << it->second << endl;
                }
            }
        }
    }

    cout << endl;

    delete[] vetorReviews;
    inputFile.close();
}

void File::arvores(int i)
{
    ifstream inputFile("tiktok_app_reviews.bin", ios::in | ios::binary);
    ofstream outputFile("saida.txt", std::ofstream::out | std::ofstream::app);

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open file" << endl;
        exit(1);
    }
    inputFile.seekg(0, std::ios::end);

    long int tam;
    cout << "Numero de registros a considerar (Minimo: 1.000.000): ";
    cin >> tam;
    srand(time(0));

    if (i == 1)
    {
        cout << endl;
        int n;
        cout << "Selecione um dos modos:" << endl;
        cout << "1 - Modo de Analise" << endl;
        cout << "2 - Modo de teste" << endl;
        cin >> n;
        cout << endl;

        string idS;

        switch (n)
        {
        case 1:

            long int b;
            cout << "Numero de registros aleatorios que a serem buscados (Minimo: 100): ";
            cin >> b;

            if (b > tam)
            {
                cout << "Numero de buscas maior que o numero de registros lidos" << endl;
                exit(1);
            }

            outputFile << "ARVORE Rubro Negra" << endl;
            outputFile << "Numero de registros a considerar: " << tam << endl;
            outputFile << "Numero de buscas: " << b << endl;

            int maxRepeat;
            cout << "Numero de repeticoes (Minimo: 3): ";
            cin >> maxRepeat;

            treeRBCaseFunction(inputFile, outputFile, tam, b, 1, maxRepeat, "");

        case 2:

            cout << "Digite o id de avaliacao a ser buscado na arvore: ";
            cin >> idS;
            treeRBCaseFunction(inputFile, outputFile, tam, b, 0, maxRepeat, idS);

            break;

        default:
            break;
        }
    }

    if (i == 2)
    {
        int ord;
        cout << "Ordem da arvore a ser usada: ";
        cin >> ord;

        cout << endl;
        int n;
        cout << "Selecione um dos modos:" << endl;
        cout << "1 - Modo de Analise" << endl;
        cout << "2 - Modo de teste" << endl;
        cin >> n;
        cout << endl;

        string idS;

        switch (n)
        {
        case 1:

            long int b;
            cout << "No modo de analise da Arvore B os valores usados para a ordem da arvore sao 20 e 200."
                 << endl
                 << "Numero de registros aleatorios a serem buscados (Minimo: 100): ";
            cin >> b;
            cout << endl;

            if (b > tam)
            {
                cout << "Numero de buscas maior que o numero de registros lidos" << endl;
                exit(1);
            }

            outputFile << "ARVORE B" << endl;
            outputFile << "Numero de registros a considerar: " << tam << endl;
            outputFile << "Numero de buscas: " << b << endl;

            int maxRepeat;
            cout << "Numero de repeticoes (Minimo: 3): ";
            cin >> maxRepeat;
            cout << endl;

            treeBCaseFunction(inputFile, outputFile, tam, b, 20, 1, maxRepeat, 0, 0, 0, 0, 0, "");

            break;

        case 2:

            cout << "Digite o id de avaliacao a ser buscado na arvore: ";
            cin >> idS;
            treeBCaseFunction(inputFile, outputFile, tam, b, ord, 0, maxRepeat, 0, 0, 0, 0, 1, idS);

            break;

        default:
            break;
        }
    }
}

void File::treeBCaseFunction(ifstream &inputFile, ofstream &outputFile, long int tam, long int b, int order, int currentCicle, int maxRepeat, long int comparacaoI, float comparacaoB, float tempoI, float tempoB, int searchId, string idS)
{
    if (!searchId)
    {
        outputFile << endl;
        outputFile << currentCicle << " - Ciclo - Ordem (" << order << ")" << endl;
    }

    TreeB tree = TreeB(order);
    Review review2;
    Analytics analyticsForInsert = Analytics();
    Analytics analyticsForSearch = Analytics();

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < tam; i++)
    {
        long int result = 1 + (rand() % (tam - 1));
        long int pos = (result - 1) * sizeof(Review);
        inputFile.seekg(pos);
        inputFile.read(reinterpret_cast<char *>(&review2), sizeof(Review));

        KeyB noArvoreB;
        noArvoreB.setPosition(pos);
        noArvoreB.setId(review2.getReview_id());

        tree.insert(noArvoreB, &analyticsForInsert);
    }

    if (searchId)
    {
        (tree.search(idS, &analyticsForSearch) != NULL) ? cout << "O ID esta presente na arvore" << endl : cout << "O ID nao esta presente na arvore" << endl;
        exit(0);
    }
    else
    {
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double, std::milli> ms_double = stop - start;

        outputFile << "Comparacoes durante as insercoes: " << analyticsForInsert.getComparisons() << endl;
        outputFile << "Tempo durante as insercoes: " << ms_double.count() << " ms" << endl;

        comparacaoI = comparacaoI + analyticsForInsert.getComparisons();
        tempoI = tempoI + ms_double.count();

        start = chrono::high_resolution_clock::now();

        for (int i = 0; i < b; i++)
        {
            long int result = 1 + (rand() % (b - 1));
            long int pos = (result - 1) * sizeof(Review);
            inputFile.seekg(pos);
            inputFile.read(reinterpret_cast<char *>(&review2), sizeof(Review));
            tree.search(review2.getReview_id(), &analyticsForSearch);
        }

        stop = chrono::high_resolution_clock::now();
        ms_double = stop - start;

        outputFile << endl;
        outputFile << "Comparacoes durante as buscas: " << analyticsForSearch.getComparisons() << endl;
        outputFile << "Tempo durante as buscas: " << ms_double.count() << " ms" << endl;

        comparacaoB = comparacaoB + analyticsForSearch.getComparisons();
        tempoB = tempoB + ms_double.count();

        tree.~TreeB();

        if (currentCicle == maxRepeat)
        {
            outputFile << endl;
            outputFile << "Media de comparacoes durante as insercoes: " << comparacaoI / maxRepeat << endl;
            outputFile << "Media de tempo durante as insercoes: " << tempoI / maxRepeat << " ms" << endl;
            outputFile << "Media de comparacoes durante as buscas: " << comparacaoB / maxRepeat << endl;
            outputFile << "Media de tempo durante as buscas: " << tempoB / maxRepeat << " ms" << endl;
            outputFile << endl;
            outputFile << "/////////////////////////////////////////////////" << endl;

            comparacaoI = 0;
            comparacaoB = 0;
            tempoI = 0;
            tempoB = 0;
        }

        while (currentCicle < maxRepeat * 2)
        {
            if (currentCicle < maxRepeat)
            {
                treeBCaseFunction(inputFile, outputFile, tam, b, 20, currentCicle + 1, maxRepeat, comparacaoI, comparacaoB, tempoI, tempoB, 0, "");
            }
            else
            {
                treeBCaseFunction(inputFile, outputFile, tam, b, 200, currentCicle + 1, maxRepeat, comparacaoI, comparacaoB, tempoI, tempoB, 0, "");
            }
        }

        if (currentCicle == maxRepeat * 2)
        {
            outputFile << endl;
            outputFile << endl;
            outputFile << "Media de comparacoes durante as insercoes: " << comparacaoI / maxRepeat << endl;
            outputFile << "Media de tempo durante as insercoes: " << tempoI / maxRepeat << " ms" << endl;
            outputFile << "Media de comparacoes durante as buscas: " << comparacaoB / maxRepeat << endl;
            outputFile << "Media de tempo durante as buscas: " << tempoB / maxRepeat << " ms" << endl;
            outputFile << endl;
            outputFile << "/////////////////////////////////////////////////" << endl;

            cout << "O arquivo saida.txt foi gerado com sucesso, e voce ja podera consultar as metricas" << endl;

            outputFile << endl;
            outputFile << "FIM" << endl;

            inputFile.close();
            outputFile.close();
            exit(0);
        }
    }
}
void File::treeRBCaseFunction(ifstream &inputFile, ofstream &outputFile, long int tam, long int b, int currentCicle, int maxRepeat, string idS)
{
    outputFile << endl;

    RBTree tree = RBTree();
    Review review2;
    Analytics analyticsForInsert = Analytics();
    Analytics analyticsForSearch = Analytics();

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < tam; i++)
    {
        long int result = 1 + (rand() % (tam - 1));
        long int pos = (result - 1) * sizeof(Review);
        inputFile.seekg(pos);
        inputFile.read(reinterpret_cast<char *>(&review2), sizeof(Review));

        string a = (review2.getReview_id());
        tree.insert(a, pos, &analyticsForInsert);
    }
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> ms_double = stop - start;

    outputFile << "Comparacoes durante as insercoes: " << analyticsForInsert.getComparisons() << endl;
    outputFile << "Tempo durante as insercoes: " << ms_double.count() << " ms" << endl;

    start = chrono::high_resolution_clock::now();

    for (int i = 0; i < b; i++)
    {

        long int result = 1 + (rand() % (b - 1));
        long int pos = (result - 1) * sizeof(Review);
        inputFile.seekg(pos);
        inputFile.read(reinterpret_cast<char *>(&review2), sizeof(Review));

        tree.search(review2.getReview_id(), &analyticsForSearch);
    }

    stop = chrono::high_resolution_clock::now();
    ms_double = stop - start;

    outputFile << endl;
    outputFile << "Comparacoes durante as buscas: " << analyticsForSearch.getComparisons() << endl;
    outputFile << "Tempo durante as buscas: " << ms_double.count() << " ms" << endl;

    tree.~RBTree();

    while (currentCicle < maxRepeat)
    {
        treeRBCaseFunction(inputFile, outputFile, tam, b, currentCicle + 1, maxRepeat, "");
    }

    if (currentCicle == maxRepeat)
    {
        cout << "O arquivo saida.txt foi gerado com sucesso, e voce ja podera consultar as metricas" << endl;

        outputFile << endl;
        outputFile << "FIM" << endl;

        inputFile.close();
        outputFile.close();
        exit(0);
    }
}

void File::generateTxtHuffman(int n, int fixedTam)
{
    ifstream inputFile("tiktok_app_reviews.bin", ios::in | ios::binary);

    string txt = "";

    long int tam;
    int repetitions = 1;

    if (fixedTam > 0)
    {
        tam = fixedTam;
        cout << "Quantas vezes voce quer rodar o ciclo (minimo 3): ";
        cin >> repetitions;
    }
    else if (n == 1)
    {
        cout << "Numero de registros a considerar: ";
        cin >> tam;
    }

    Huffman huffmanDecomp = Huffman();
    Analytics analyticsDecomp = Analytics();

    if (n == 1 || n == 3)
    {
        int totalComparacoes = 0;
        long int inputBytesSum = 0;
        long int outputBytesSum = 0;

        for (int i = 0; i < repetitions; i++)
        {
            Analytics analytics = Analytics();
            Huffman huffmanComp = Huffman();

            srand(time(0));

            if (!inputFile.is_open())
            {
                cout << "Error: Could not open file" << endl;
                exit(1);
            }

            inputFile.seekg(0, std::ios::end);

            Review reviewAux;
            for (int i = 0; i < tam; i++)
            {
                long int result = 1 + (rand() % (3660724 - 1));
                long int pos = (result - 1) * sizeof(Review);
                inputFile.seekg(pos);
                inputFile.read(reinterpret_cast<char *>(&reviewAux), sizeof(Review));
                txt += reviewAux.getReview_text();
            }

            huffmanComp.buildHuffmanTree(txt, n, &analytics, i);

            totalComparacoes += analytics.getComparisons();
            inputBytesSum += analytics.getInputBytes();
            outputBytesSum += analytics.getoutputBytes();
        }

        if (n == 3)
        {
            ifstream inputFile("reviewsComp.bin", ios::in | ios::binary);
            ofstream outputFile("saida.txt", std::ofstream::out | std::ofstream::app);

            inputFile.seekg(0, ios::end);
            int file_size = inputFile.tellg();

            float media = totalComparacoes / repetitions;

            outputFile << endl << endl << "Media de comparacoes: " << media << endl;
            outputFile << "Media da taxa de compressao: " << (((double)inputBytesSum - outputBytesSum) / inputBytesSum) * 100 << "%" << endl;
        }
    }
    else
    {
        huffmanDecomp.buildHuffmanTree(txt, n, &analyticsDecomp, 1);
    }

    return;
}
