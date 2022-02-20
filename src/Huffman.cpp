
#include "Huffman.h"
#include "Analytics.h"
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

struct HuffmanNo
{
	char reviewsText;
	int frequency;
	HuffmanNo *left, *right;
};

struct comparison
{
	bool operator()(HuffmanNo *lft, HuffmanNo *rgt)
	{
		return lft->frequency > rgt->frequency;
	}
};

HuffmanNo *getHuffmanNo(char reviewsText, int frequency, HuffmanNo *left, HuffmanNo *right)
{
	HuffmanNo *no = new HuffmanNo();

	no->left = left;
	no->right = right;
	no->reviewsText = reviewsText;
	no->frequency = frequency;

	return no;
}


void encode(HuffmanNo *rt, string str, unordered_map<char, string> &hfCode, Analytics *analytics)
{

	analytics->addComparisons();

	if (rt == nullptr)
		return;

	if (!rt->left && !rt->right)
	{
		hfCode[rt->reviewsText] = str;
	}

	encode(rt->left, str + "0", hfCode, analytics);
	encode(rt->right, str + "1", hfCode, analytics);
}

void decode(HuffmanNo *rt, int &idx, string str)
{
	ofstream outputFile("reviewsOrig.bin", ios::out | ios::app | ios::binary);
	ifstream inputFile("reviewsOrig.bin", ios::in | ios::binary);

	if (rt == nullptr)
	{
		return;
	}

	if (!rt->left && !rt->right)
	{
		outputFile << rt->reviewsText;
		return;
	}

	idx++;

	if (str[idx] == '0')
		decode(rt->left, idx, str);
	else
		decode(rt->right, idx, str);
}

void decompression(string txtParam, int n)
{
	string filename = "temp.txt";

	ifstream inputFile("reviewsComp.bin", ios::binary);
	ifstream arq(filename, ios::in);

	string txt = txtParam;

	if (arq.is_open())
	{
		while (!arq.eof())
		{
			getline(arq, txt);
		}
		arq.close();
	}

	unordered_map<char, int> frequency;
	for (char reviewsText : txt)
	{
		frequency[reviewsText]++;
	}

	priority_queue<HuffmanNo *, vector<HuffmanNo *>, comparison> prioQueue;

	for (auto pair : frequency)
	{
		prioQueue.push(getHuffmanNo(pair.first, pair.second, nullptr, nullptr));
	}

	while (prioQueue.size() != 1)
	{
		HuffmanNo *left = prioQueue.top();
		prioQueue.pop();
		HuffmanNo *right = prioQueue.top();
		prioQueue.pop();

		int sum = left->frequency + right->frequency;
		prioQueue.push(getHuffmanNo('\0', sum, left, right));
	}

	HuffmanNo *rt = prioQueue.top();

	unordered_map<char, string> hfCode;

	string str = "";

	inputFile.seekg(0, inputFile.end);
	int length = inputFile.tellg();
	inputFile.seekg(0, inputFile.beg);
	char *buffer = new char[length];
	inputFile.read(buffer, length);
	str = string(buffer, length);
	delete[] buffer;

	int idx = -1;
	while (idx < (int)str.size() - 2)
	{
		decode(rt, idx, str);
	}
}

void auxTest(string path, string bin)
{
	ofstream arq;
	arq.open(path, ios::binary);

	arq << bin;
	arq.close();
}

long int compression(string txtParam, int n, Analytics *analytics)
{
	ofstream outputFile("reviewsComp.bin", ios::out | ios::trunc | ios::binary);
	ofstream outputFile2("temp.txt", ios::out | ios::trunc);

	string txt = txtParam;

	outputFile2 << txt;

	unordered_map<char, int> frequency;
	for (char reviewsText : txt)
	{
		frequency[reviewsText]++;
	}

	priority_queue<HuffmanNo *, vector<HuffmanNo *>, comparison> prioQueue;

	for (auto pair : frequency)
	{
		prioQueue.push(getHuffmanNo(pair.first, pair.second, nullptr, nullptr));
	}

	while (prioQueue.size() != 1)
	{
		HuffmanNo *left = prioQueue.top();
		prioQueue.pop();
		HuffmanNo *right = prioQueue.top();
		prioQueue.pop();

		int sum = left->frequency + right->frequency;
		prioQueue.push(getHuffmanNo('\0', sum, left, right));
	}

	HuffmanNo *rt = prioQueue.top();

	unordered_map<char, string> hfCode;
	encode(rt, "", hfCode, analytics);

	string str = "";

	for (char ch : txt)
	{
		str += hfCode[ch];
	}

	outputFile.write(str.c_str(), str.length());

	return str.size() / 8;
}

void Huffman::buildHuffmanTree(string text, int n, Analytics *analytics, int cycle)
{
	if (n == 1 || n == 3)
	{

		long int bytesOutput = compression(text, n, analytics);

		analytics->addInputBytes(text.size());
		analytics->addOutputBytes(bytesOutput);

		if (n == 3)
		{
			ofstream outputFile("saida.txt", std::ofstream::out | std::ofstream::app);

			outputFile << cycle + 1 << " Compressao" << endl;
			outputFile << "total de comparacoes no ciclo " << cycle + 1 << ": " << analytics->getComparisons() << endl;
			outputFile << "total de bytes de entrada " << text.size() << endl;
			outputFile << "total de bytes de saida " << bytesOutput << endl;
			outputFile << "taxa de compressao " << (((double)text.size() - bytesOutput) / text.size()) * 100 << "%"<< endl;
		}
	}

	if (n == 2)
	{
		decompression(text, n);
	}
}