#include<iostream>

using namespace std;

class NoB
{
	int *chave; 
	int t;	 
	NoB **filhos;
	int n;	 
	bool folha; 
public:
	NoB(int _t, bool _folha); 
	void insertNonFull(int k);
	void splitChild(int i, NoB *y);
	NoB *search(int k); 

friend class ArvoreB;
};

class ArvoreB
{
	NoB *raiz; 
	int t; 
public:
	ArvoreB(int _t)
	{ raiz = NULL; t = _t; }

	NoB* search(int k)
	{ return (raiz == NULL)? NULL : raiz->search(k); }

	void insert(int k);
};

NoB::NoB(int t1, bool folha1)
{
	t = t1;
	folha = folha1;

	chave = new int[2*t-1];
	filhos = new NoB *[2*t];

	n = 0;
}

NoB *NoB::search(int k)
{
	int i = 0;
	while (i < n && k > chave[i])
		i++;

	if (chave[i] == k)
		return this;

	if (folha == true)
		return NULL;

	return filhos[i]->search(k);
}

void ArvoreB::insert(int k)
{
	if (raiz == NULL)
	{
		raiz = new NoB(t, true);
		raiz->chave[0] = k;
		raiz->n = 1; 
	}
	else
	{
		if (raiz->n == 2*t-1)
		{			
			NoB *s = new NoB(t, false);

			s->filhos[0] = raiz;

			s->splitChild(0, raiz);

			int i = 0;
			if (s->chave[0] < k)
				i++;
			s->filhos[i]->insertNonFull(k);

			raiz = s;
		}
		else
			raiz->insertNonFull(k);
	}
}

void NoB::insertNonFull(int k)
{
	int i = n-1;

	if (folha == true)
	{
		while (i >= 0 && chave[i] > k)
		{
			chave[i+1] = chave[i];
			i--;
		}

		chave[i+1] = k;
		n = n+1;
	}
	else
	{
		while (i >= 0 && chave[i] > k)
			i--;

		if (filhos[i+1]->n == 2*t-1)
		{
			splitChild(i+1, filhos[i+1]);

			if (chave[i+1] < k)
				i++;
		}
		filhos[i+1]->insertNonFull(k);
	}
}

void NoB::splitChild(int i, NoB *y)
{
	NoB *z = new NoB(y->t, y->folha);
	z->n = t - 1;

	for (int j = 0; j < t-1; j++)
		z->chave[j] = y->chave[j+t];

	if (y->folha == false)
	{
		for (int j = 0; j < t; j++)
			z->filhos[j] = y->filhos[j+t];
	}

	y->n = t - 1;

	for (int j = n; j >= i+1; j--)
		filhos[j+1] = filhos[j];

	filhos[i+1] = z;

	for (int j = n-1; j >= i; j--)
		chave[j+1] = chave[j];

	chave[i] = y->chave[t-1];

	n = n + 1;
}
