#include "Review.h"
#include "File.h"
#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

void openFile(int i)
{

    File file;

    vector<Review> review;
    vector<Review> teste;

    file.readFile(&review, "tiktok_app_reviews.csv");

    //file.writeTxt(&review);

    file.writeBin(&review);

    if (i == 1)
    {
        file.testeImportacao();
    }
    else if (i == 2)
    {
        long int n;
        cout << "Digite um numero para acessar diretamente o registro correspondente no arquivo binario: ";
        cin >> n;
        file.acessaRegistro(n);
    }

    //file.readBinary(&teste);
}

void Menu()
{
    int i;
    cout << "MENU:" << endl;
    cout << "Digite 1 para acessar o modulo de teste ou 2 para acessar um registro do arquivo: ";
    cin >> i;
    openFile(i);
}

int main()
{
    Menu();
    cout << "Fim" << endl;
    return 0;
}