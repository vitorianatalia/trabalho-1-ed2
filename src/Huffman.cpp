
#include "Huffman.h"
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
using namespace std;

// A Tree node
struct HuffmanNo
{
	char reviewsText;
	int frequency;
	HuffmanNo *left, *right;
};

// Function to allocate a new tree node
HuffmanNo *getHuffmanNo(char reviewsText, int frequency, HuffmanNo *left, HuffmanNo *right)
{
	HuffmanNo *no = new HuffmanNo();

	no->left = left;
	no->right = right;
	no->reviewsText = reviewsText;
	no->frequency = frequency;

	return no;
}

// Comparison object to be used to order the heap
struct comparison
{
	bool operator()(HuffmanNo *lft, HuffmanNo *rgt)
	{
		// highest priority item has lowest frequencyuency
		return lft->frequency > rgt->frequency;
	}
};

// traverse the Huffman Tree and store Huffman Codes
// in a map.
void encode(HuffmanNo *rt, string str, unordered_map<char, string> &hfCode)
{
	if (rt == nullptr)
		return;

	// found a leaf node
	if (!rt->left && !rt->right)
	{
		hfCode[rt->reviewsText] = str;
	}

	encode(rt->left, str + "0", hfCode);
	encode(rt->right, str + "1", hfCode);
}

// traverse the Huffman Tree and decode the encoded string
void decode(HuffmanNo *rt, int &idx, string str)
{
	if (rt == nullptr)
	{
		return;
	}

	// found a leaf node
	if (!rt->left && !rt->right)
	{
		cout << rt->reviewsText;
		return;
	}

	idx++;

	if (str[idx] == '0')
		decode(rt->left, idx, str);
	else
		decode(rt->right, idx, str);
}

// Builds Huffman Tree and decode given input text
void run(string txtParam, int n)
{
	ofstream outputFile("reviewsComp.bin", ios::out | ios::trunc | ios::binary);
	ifstream inputFile("reviewsComp.bin", ios::in | ios::binary);

	string txt = txtParam;

	unordered_map<char, int> frequency;
	for (char reviewsText : txt)
	{
		frequency[reviewsText]++;
	}

	priority_queue<HuffmanNo *, vector<HuffmanNo *>, comparison> pq;

	for (auto pair : frequency)
	{
		pq.push(getHuffmanNo(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		HuffmanNo *left = pq.top();
		pq.pop();
		HuffmanNo *right = pq.top();
		pq.pop();

		int sum = left->frequency + right->frequency;
		pq.push(getHuffmanNo('\0', sum, left, right));
	}

	HuffmanNo *rt = pq.top();

	unordered_map<char, string> hfCode;
	encode(rt, "", hfCode);

	string str = "";
	if (n == 2)
	{
		// str equals content in binary file
		inputFile.seekg(0, inputFile.end);
		int length = inputFile.tellg();
		inputFile.seekg(0, inputFile.beg);
		char *buffer = new char[length];
		inputFile.read(buffer, length);
		str = string(buffer, length);
		delete[] buffer;

		cout << "Texto que veio do arquivo" << str << endl;
	}
	else
	{
		for (char ch : txt)
		{
			str += hfCode[ch];
		}
	}

	if (n == 1)
	{
		// write str in binary file
		outputFile.write(str.c_str(), str.length());

		// outputFile.write((char *)&str, sizeof(str));

		cout << "Foi gerado o arquivo reviewsComp binario com sucesso!" << endl;
	}
	else
	{
		int idx = -1;
		while (idx < (int)str.size() - 2)
		{
			decode(rt, idx, str);
		}
	}
}

void Huffman::buildHuffmanTree(string text, int n)
{
	run(text, n);
}
