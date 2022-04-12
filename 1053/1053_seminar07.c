#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct AparatFoto AparatFoto;
typedef struct Nod Nod;
typedef struct HashTable HashTable;


struct AparatFoto {
	char* marca;
	float pret;
};

struct Nod {
	Nod* next;
	AparatFoto info;
};

struct HashTable {
	Nod** vector;
	int nr;
};

AparatFoto initializareAparatFoto(const char* marca1, float pret)
{
	AparatFoto a1;
	a1.marca = (char*)malloc(sizeof(char) * (strlen(marca1) + 1));
	strcpy(a1.marca, marca1);
	a1.pret = pret;
	return a1;
}

void afisareAparatFoto(AparatFoto a)
{
	printf("Aparatul foto cu marca %s si pretul %f\n", a.marca, a.pret);
}

int functieHT(char* marca, int nrElemente)
{
	return (strlen(marca) % nrElemente);
}

HashTable initializareHT(int nrElemente) {
	HashTable h;
	h.nr = nrElemente;
	h.vector = (Nod**)malloc(sizeof(Nod*) * nrElemente);
	for (int i = 0; i < nrElemente; i++) {
		h.vector[i] = NULL;
	}


	return h;
}

void inserareLaSfarsit(Nod** cap, AparatFoto a) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = a;
	nou->next = NULL;
	if (*cap) {
		Nod* aux = *cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

void inserareHashTable(AparatFoto a, HashTable h) {
	if (h.nr > 0) {
		int poz = functieHT(a.marca, h.nr);
		if (poz >= 0 && poz < h.nr) {
			inserareLaSfarsit(&(h.vector[poz]), a);
		}
	}
}

void afisareHT(HashTable h) {
	for (int i = 0; i < h.nr; i++)
	{	if (h.vector[i] != NULL) {
			Nod* aux = h.vector[i];
			while (aux) {
				printf("poz %d\n", i);
				afisareAparatFoto(aux->info);
				aux = aux->next;
			}
		}
		else {
			printf("poz goala %d\n", i);
		}
	}
}

int main()
{
	HashTable t = initializareHT(5);
	inserareHashTable(initializareAparatFoto("Nikon", 2400), t);
	inserareHashTable(initializareAparatFoto("Canon", 2300), t);
	inserareHashTable(initializareAparatFoto("Parasonic", 2390), t);

	afisareHT(t);
	return 0;
}