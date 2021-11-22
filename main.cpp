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
        cout << "0 - Sair" << endl;
        cout << "========================================= " << endl;

        cin >> i;

        switch (i) {
            case 0:
                break;
            case 1: case 2:
                openFile(i);
                break;
            default:
                cout << "Valor digitado invalido" << endl;
        }
    } while(i);
}

int main()
{
    menu();
    cout << "Programa encerrado" << endl;
    return 0;
}