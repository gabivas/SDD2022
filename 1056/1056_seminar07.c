#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct Desert Desert;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Desert {
	char* denumire;
	double pret;
};

struct Nod {
	Desert info;
	Nod* next;
};

struct HashTable {
	int nrElemente;
	Nod** vector;
};

Desert creareDesert(const char* denumire, double pret) {
	Desert d1;
	d1.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(d1.denumire, denumire);
	d1.pret = pret;

	return d1;
}

void afisareDesert(Desert d) {
	printf("Desertul %s are pretul %.2f", d.denumire, d.pret);
}

int functieHash(char* denumire, int nrElemente) {
	return strlen(denumire) % nrElemente;
}

HashTable initializareHashTable(int nrElemente)
{
	HashTable hashTable;
	hashTable.nrElemente = nrElemente;
	hashTable.vector = (Nod**)malloc(sizeof(Nod*) * nrElemente);
	for (int i = 0; i < nrElemente; i++)
	{
		hashTable.vector[i] = NULL;
	}
	return hashTable;
}

void inserareFinal(Nod** cap, Desert d)
{
	Nod* nou;
	nou = (Nod*)malloc(1 * (sizeof(Nod)));
	nou->info = d;
	nou->next = NULL;
	if (*cap)
	{
		Nod* aux = *cap;

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

void inserareHT(HashTable  ht, Desert d)
{
	if (ht.nrElemente > 0)
	{
		int poz = functieHash(d.denumire, ht.nrElemente);
		if (poz < ht.nrElemente && poz >= 0)
		{
			inserareFinal(&(ht.vector[poz]), d);
		}

	}
}

void afisareHt(HashTable ht)
{
	for (int i = 0; i < ht.nrElemente; i++)
	{
		if (ht.vector[i])
		{
			Nod* aux = ht.vector[i];
			while (aux)
			{
				printf("\nPozitie in ht: %i\n", i);
				afisareDesert(aux->info);
				aux = aux->next;
			}

		}
		else
		{
			printf("Pozitie libera in ht: %i\n", i);
		}
	}

}

int main() {

	HashTable ht;

	ht = initializareHashTable(5);
	inserareHT(ht, creareDesert("tiramisu", 12.99));
	inserareHT(ht, creareDesert("savarina", 10.99));
	inserareHT(ht, creareDesert("amandina", 9.99));
	inserareHT(ht, creareDesert("tort", 39.99));
	inserareHT(ht, creareDesert("crema de zahar ars", 19.99));

	afisareHt(ht);


}