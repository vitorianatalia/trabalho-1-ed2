#include "Review.h"
#include "File.h"
#include "Hash.h"
#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include "TreeB.h"
#include "NoB.h"

using namespace std;

void openFile(int i, string path)
{
    File file;
    vector<Review> review;

    file.readFile(&review, path);
    file.writeBin(&review);

    long int n;

    switch (i)
    {
    case 1:

        cout << endl;
        cout << "Quantidade de registros a considerar: ";
        cin >> n;

        file.runHash(n, 0);

        break;

    case 2:
        cout << "1 - Teste dos algoritmos de ordenacao" << endl;
        for (int j = 1; j < 4; j++)
            file.testVector(100, 3, j);
        cout << "2 - Teste de versoes mais frequentes" << endl;
        file.runHash(100, 1);
        cout << "3 - Teste de importacao" << endl;
        file.testeImportacao();
        break;

    case 3:
        int m;
        int algorithm;

        cout << endl;
        cout << "Algoritmo de ordenacao: " << endl;
        cout << "1 - HeapSort" << endl;
        cout << "2 - CountingSort" << endl;
        cout << "3 - QuickSort" << endl;
        cin >> algorithm;

        cout << endl;
        cout << "Quantas vezes deseja executar o algoritmo (minimo 3): " << endl;
        cin >> m;

        cout << endl;
        cout << "Quantos valores deseja ordenar: " << endl;
        cout << "1 - 10.000" << endl;
        cout << "2 - 50.000" << endl;
        cout << "3 - 100.000" << endl;
        cout << "4 - 500.000" << endl;
        cout << "5 - 1.000.000" << endl;
        cin >> n;

        if (n <= 0 || n > 5 || m < 3)
        {
            cout << "Valores invalidos" << endl;
            return;
        }

        n = n == 1 ? 10000 : n == 2 ? 50000
                         : n == 3   ? 100000
                         : n == 4   ? 500000
                                    : 1000000;

        file.generateVector(n, m, algorithm);
        break;

    case 4:
        int n;
        cout << "Selecione uma das arvores a seguir:" << endl;
        cout << "1 - Arvore Vermelho-Preto" << endl;
        cout << "2 - Arvore B." << endl;
        cout << "3 - Sair" << endl;
        cin >> n;
        cout << endl;
        if (n == 1 || n == 2)
        {
            file.arvores(n);
        }
        break;

    case 5:

        cout << "1 - Comprimir um conjunto de dados e salvar no arquivo reviewsComp" << endl;
        cout << "2 - Descomprimir um conjunto de dados e salvar no arquivo reviewsOrig" << endl;
        cout << "3 - Executar uma sequencia de compressoes de N (usar os valores 10.000, 100.000 e 1.000.000) reviews_texts aleatorios" << endl;
        cin >> n;

        if (n == 3)
        {
            int auxN;

            cout << "1 - 10.000" << endl;
            cout << "2 - 100.000" << endl;
            cout << "3 - 1.000.000" << endl;

            cin >> auxN;

            auxN = auxN == 1 ? 10000 : auxN == 2 ? 100000
                                                 : 1000000;

            file.generateTxtHuffman(n, auxN);
        }
        else
            file.generateTxtHuffman(n, -1);
        break;
    default:
        break;
    }
}

void menu(string path)
{
    int i;

    do
    {
        cout << "========================================= " << endl;
        cout << "\t\tMENU:" << endl;
        cout << "1 - Hash" << endl;
        cout << "2 - Modulo de Teste" << endl;
        cout << "3 - Ordenacao" << endl;
        cout << "4 - Arvores" << endl;
        cout << "5 - Huffman" << endl;
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
            openFile(i, path);
            break;
        default:
            cout << "Valor digitado invalido" << endl;
        }
    } while (i);
}

int main(int argc, char *argv[])
{
    string path;
    path = argv[1];

    menu(path);

    cout << "Programa encerrado" << endl;
    return 0;
}