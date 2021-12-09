#include "Review.h"
#include "File.h"
#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
using namespace std;

void quicksort(Review *reviews, int left, int right)
{
    int i = left;
    int j = right;
    Review pivot = reviews[(left + right) / 2];

    while (i <= j)
    {
        while (reviews[i].getUpvotes() < pivot.getUpvotes())
        {
            i++;
        }
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
        }
    }
    if (left < j)
    {
        quicksort(reviews, left, j);
    }
    if (i < right)
    {
        quicksort(reviews, i, right);
    }
}


void openFile(int i)
{
    File file;

    vector<Review> review;

    file.readFile(&review, "tiktok_app_reviews.csv");
    file.writeBin(&review);

    if (i == 1)
    {
        file.testeImportacao();
    }
    else if (i == 2)
    {
        long int n;
        cout << "Digite 1 numero para acessar diretamente o registro correspondente no arquivo binario: ";
        cin >> n;
        file.acessaRegistro(n);
    }

    else if (i == 3)
    {
        quicksort(review.data(), 0, review.size() - 1);

        for (int i = 1; i < review.size() - 1; i++)
        {
            cout << review[i].getUpvotes() << endl;
        }
    }

    else if (i == 4)
    {
        long int n;
        cout << "Digite a quantia de números aleatórios: ";
        cin >> n;
        file.geraVetor(n);
    }

    else if (i == 5)
    {
        long int n;
        cout << "Insira um número de registros:" << endl;
        cin >> n;
        file.generateVector(n);
    }
    
   
}

void menu()
{
    int i;

    do
    {
        cout << "========================================= " << endl;
        cout << "\t\tMENU:" << endl;
        cout << "1 - Acessar modulo de testes" << endl;
        cout << "2 - Acessar registro do arquivo" << endl;
        cout << "3 - Quicksort" << endl;
        cout << "4 - Heapsort" << endl;
        cout << "5 - Gerar N registros" << endl;
        cout << "0 - Sair" << endl;
        cout << "========================================= " << endl;

        cin >> i;

        switch (i)
        {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                openFile(i);
                break;
            default:
                cout << "Valor digitado invalido" << endl;
        }
    } while (i);
}

int main()
{
    menu();
    cout << "Programa encerrado" << endl;
    return 0;
}