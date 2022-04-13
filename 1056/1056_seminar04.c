#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

struct Carte
{
	char* titlu;
	int nrPagini;
};

struct Nod
{
	struct Carte inf;
	struct Nod* next;
};

struct Carte creareCarte(char* _titlu, int _nrPagini)
{
	struct Carte carte;
	carte.titlu = (char*)malloc((strlen(_titlu) + 1) * sizeof(char));
	strcpy(carte.titlu, _titlu);
	carte.nrPagini = _nrPagini;
	return carte;
}

void inserareInceput(struct Nod** cap, struct Carte _carte)
{
	struct Nod* nou;
	nou = (struct Nod*)malloc(sizeof(struct Nod));
	nou->inf = _carte;
	nou->next = *cap;
	*cap = nou;
}

void inserareFinal(struct Nod** cap, struct Carte carte)
{
	struct Nod* aux;
	aux = *cap;
	struct Nod* n = (struct Nod*)malloc(sizeof(struct Nod));
	n->inf = carte;
	n->next = NULL;

	if (*cap) {
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = n;
	}
	else
	{
		*cap = n;
	}
}
void afisareCarte(struct Carte _carte) {
	printf("Cartea %s are %d pagini.\n", _carte.titlu, _carte.nrPagini);
}

void afisareListCarti(struct Nod* cap) {
	while (cap) {
		afisareCarte(cap->inf);
		cap = cap->next;
	}
}

void dezalocare(struct Nod** cap)
{
	while (*cap)
	{
		free((*cap)->inf.titlu);
		struct Nod* aux = *cap;
		(*cap) = (*cap)->next;
		free(aux);
	}
}

void main()
{
	struct Nod* cap = NULL;

	inserareInceput(&cap, creareCarte("Magicianul", 700));
	inserareFinal(&cap, creareCarte("Baltagul", 200));
	inserareFinal(&cap, creareCarte("Si-a fost seara, si-a fost dimineata", 953));

	afisareListCarti(cap);
	dezalocare(&cap);
	afisareListCarti(cap);
}