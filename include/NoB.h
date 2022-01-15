#ifndef NOB_H_INCLUDED
#define NOB_H_INCLUDED

#include <iostream>
#include "TreeB.h"

using namespace std;

class NoB
{
private:
	int minDegree;		  // t;
	NoB **children;		  // c;
	int currentTotalNode; // n ;
	bool leaf;
	KeyB *key;

	friend class TreeB;

public:
	NoB(int t1, bool leafParam)
	{
		minDegree = t1;
		leaf = leafParam;

		key = new KeyB[2 * minDegree - 1];
		children = new NoB *[2 * minDegree];
		currentTotalNode = 0;
	}

	void splitChild(int i, NoB *node)
	{

		NoB *aux = new NoB(node->minDegree, node->leaf);
		aux->currentTotalNode = minDegree - 1;

		for (int j = 0; j < minDegree - 1; j++)
		{
			aux->key[j] = node->key[j + minDegree];
		}

		if (node->leaf == false)
		{
			for (int j = 0; j < minDegree; j++)
				aux->children[j] = node->children[j + minDegree];
		}

		node->currentTotalNode = minDegree - 1;

		for (int j = currentTotalNode; j >= i + 1; j--)
		{
			children[j + 1] = children[j];
		}

		children[i + 1] = aux;

		for (int j = currentTotalNode - 1; j >= i; j--)
		{
			key[j + 1] = key[j];
		}

		key[i] = node->key[minDegree - 1];

		currentTotalNode = currentTotalNode + 1;
	}

	void insertNonFull(KeyB no)
	{
		int i = currentTotalNode - 1;

		if (leaf == true)
		{
			while (i >= 0 && key[i].getId() > no.getId())
			{
				key[i + 1] = key[i];
				i--;
			}

			key[i + 1] = no;
			currentTotalNode = currentTotalNode + 1;
		}
		else
		{
			while (i >= 0 && key[i].getId() > no.getId())
			{
				i--;
			}

			if (children[i + 1]->currentTotalNode == 2 * minDegree - 1)
			{
				splitChild(i + 1, children[i + 1]);

				if (key[i + 1].getId() < no.getId())
				{
					i++;
				}
			}
			children[i + 1]->insertNonFull(no);
		}
	}

	NoB *search(KeyB no)
	{
		int i = 0;
		while (i < currentTotalNode && no.getId() > key[i].getId())
			i++;

		if (key[i].getId() == no.getId())
			return this;

		if (leaf == true)
			return NULL;

		return children[i]->search(no);
	}

	void traverse()
	{
		int i;
		for (i = 0; i < currentTotalNode; i++)
		{
			if (leaf == false)
				children[i]->traverse();
			cout << " " << key[i].getId();
			cout << endl;
		}

		if (leaf == false)
			children[i]->traverse();
	}
};

#endif