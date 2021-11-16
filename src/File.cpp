#include "File.h"
#include "Review.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

void File::readFile(vector<Review> *reviewList, string filename)
{
    ifstream arq(filename.c_str(), ios::in);
    Review review;
    int contador = 0;

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
        contador++;
    }
    //cout << reviewList->size() << endl;
    return;
}

void File::writeTxt(vector<Review> *reviewList)
{
    ofstream outputFile("teste.txt", std::ofstream::out | std::ofstream::trunc);

    for (int i = 0; i < reviewList->size(); i++)
    {

        outputFile << i + 1 << "- Linha" << endl;
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
    ofstream outputFile("teste.bin", ios::out | ios::trunc | ios::binary);

    for (int i = 0; i < reviewList->size(); i++)
    {
        //cout << "write binary " << &reviewList->at(i) << endl;
        outputFile.write(reinterpret_cast<char *>(&reviewList->at(i)), sizeof(Review));
    }

    outputFile.close();
}

void File::readBinary(vector<Review> *reviewList)
{
    ifstream inputFile("teste.bin", ios::in | ios::binary);

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open file" << endl;
        exit(1);
    }

    Review review;

    int contador = 0;
    while (inputFile.read(reinterpret_cast<char *>(&review), sizeof(Review)))
    {
        reviewList->push_back(review);
        contador++;
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
        cout << "versao:" << reviewList->at(i).getAppVersion() << endl;
        cout << "data:" << reviewList->at(i).getPostedDate() << endl;
        cout << "id:" << reviewList->at(i).getReview_id() << endl;
        cout << "texto:" << reviewList->at(i).getReview_text() << endl;
        cout << "likes:" << reviewList->at(i).getUpvotes() << endl;
        cout << endl;
    }
}


void File::acessaRegistro(int n)
{
    ifstream inputFile("teste.bin", ios::in | ios::binary);

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open file" << endl;
        exit(1);
    }

    Review review;

    int pos = (n - 1) * sizeof(Review);
    inputFile.seekg(pos);
    inputFile.read(reinterpret_cast<char *>(&review), sizeof(Review));

    cout << "ID: " << review.getReview_id() << endl;
    cout << "Texto: " << review.getReview_text() << endl;
    cout << "Votos: " << review.getUpvotes() << endl;
    cout << "Versao: " << review.getAppVersion() << endl;
    cout << "Data: " << review.getPostedDate() << endl;
    cout << endl;
}

void File::testeImportacao(int n, vector<Review> *reviewList)
{
    

    if (n == 1) //saida em console
    {
        vector<Review> randomReview;
        Review line;
        for (int i=0; i<10; i++) {
            int result = 1 + (rand() % reviewList->size()-1);
            cout << result << endl;
            line = reviewList->at(result);
            randomReview.push_back(line);
            cout << "contador: " << i << endl << endl;
        }
        printConsole(&randomReview);
    }
    else if (n == 2) //saida em texto
    {
        vector<Review> randomReview;
        Review line;
        for (int i=0; i<100; i++) {
            int result = 1 + (rand() % reviewList->size()-1);
            cout << result << endl;
            line = reviewList->at(result);
            randomReview.push_back(line);
            cout << "contador: " << i << endl << endl;
        }
        writeTxt(&randomReview);
    }
}

