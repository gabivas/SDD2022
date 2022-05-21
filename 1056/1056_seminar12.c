#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
typedef struct Oras Oras;

struct Oras {
	int id;
	char* den;
	int populatie;
};

struct NodPrincipal {
	Oras inf;
	NodPrincipal* next;
	NodSecundar* vecini; //lista vecini
};

struct NodSecundar {
	NodPrincipal* inf;
	NodSecundar* next;
};

Oras initOras(int id, const char* den, int populatie)
{
	Oras oras;
	oras.id = id;
	oras.den = (char*)malloc(strlen(den) + 1);
	strcpy(oras.den, den);
	oras.populatie = populatie;
	return oras;
}

void inserarelistaprincipala(NodPrincipal** cap, Oras oras) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->inf = oras;
	nou->next = NULL;
	nou->vecini = NULL;
	NodPrincipal* aux = *cap;
	if (*cap) {
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}
void inserareLS(NodSecundar** cap, NodPrincipal* info)
{
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->inf = info;
	nou->next = NULL;
	if (*cap)
	{
		NodSecundar* aux = *cap;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
	{
		*cap = nou;
	}
}

void afisareOras(Oras o) {
	printf("\norasul cu idul %d si cu numele %s are %d locuitori", o.id, o.den, o.populatie);
}

void afisareLista(NodPrincipal* np) {
	while (np) {
		afisareOras(np->inf);
		NodSecundar* aux = np->vecini;
		printf("\nvecini: ");
		while (aux) {
			afisareOras(aux->inf->inf);
			aux = aux->next;
		}
		printf("\n");
		np = np->next;
	}
}

NodPrincipal* cautareNod(NodPrincipal* nod, int id)
{
	while (nod && nod->inf.id != id)
	{
		nod = nod->next;
	}
	return nod;
}

void inserareVecini(NodPrincipal* nod, int id1, int id2)
{
	NodPrincipal* nod1 = cautareNod(nod, id1);
	NodPrincipal* nod2 = cautareNod(nod, id2);
	if (nod1 != NULL && nod2 != NULL)
	{
		inserareLS(&nod1->vecini, nod2);
		inserareLS(&nod2->vecini, nod1);
	}
}

void main() {
	NodPrincipal* cap = NULL;

	inserarelistaprincipala(&cap, initOras(2, "Buc", 10));
	inserarelistaprincipala(&cap, initOras(3, "Cluj", 10));
	inserarelistaprincipala(&cap, initOras(4, "Timisoara", 10));
	inserarelistaprincipala(&cap, initOras(5, "Ploiesti", 10));
	inserarelistaprincipala(&cap, initOras(6, "Arad", 10));

	inserareVecini(cap, 2, 4);
	inserareVecini(cap, 3, 6);
	inserareVecini(cap, 3, 5);
	inserareVecini(cap, 4, 3);
	inserareVecini(cap, 4, 5);

	afisareLista(cap);
}