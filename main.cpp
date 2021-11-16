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

    file.readFile(&review, "teste.csv");

    //file.writeTxt(&review);

    file.writeBin(&review);

    if (i == 1)
    {
        int n;
        cout << "Digite 1 para a saída no console ou 2 para a saída em arquivo .txt:";
        cin >> n;
        file.testeImportacao(n, &review);
    }
    else if (i == 2)
    {
        int n;
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
    cout << "Digite 1 para entrar acessar o módulo de teste ou 2 para acessar um registro do arquivo:" << endl;
    cin >> i;
    openFile(i);
}

int main()
{
    Menu();
    cout << "Fim" << endl;
    return 0;
}