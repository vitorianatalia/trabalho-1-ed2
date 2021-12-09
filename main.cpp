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

void countingsort(long *reviews, const long n)
{
    long i;
    long largest = reviews[0];
    long *tmp = new long[n];

    for(i = 1; i< n; i++)
    {
        if(largest < reviews[i])
        largest  = reviews[i];
    }

    unsigned long *count = new unsigned long[largest+1];

    for(i = 0; i <= largest; i++)
    {
        count[i] = 0;
    }

    for(i = 0; i < n; i++)
    {
        count[reviews[i]]++;
    }

    for(i = 1; i <= largest; i++)
    {
        count[i] = count[i-1] + count[i];
    }

    for(i = n-1; i >= 0; i++)
    {
        tmp[count[reviews[i]] - 1] = reviews[i];
        count[reviews[i]]--;
    }

    for(i = 0; i <= n; i++)
    {
        reviews[i] = tmp[i];
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

    else if ( i == 5)
    {
        int n;
        cout << "Insira um número de registros:" << endl;
        cin >> n;
        countingsort(review.data(),n);
    }
    
    else if (i == 4)
    {
        long int n;
        cout << "Digite a quantia de números aleatórios: ";
        cin >> n;
        file.geraVetor(n);
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