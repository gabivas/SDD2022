#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

struct Meniu {
	int pret;
	char* denumire;
};

struct Nod {
	struct Meniu info;
	struct Nod* next;
};

struct Meniu creareMeniu(int pret, char* denumire) {
	struct Meniu meniu;
	meniu.pret = pret;
	meniu.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(meniu.denumire, denumire);

	return meniu;
}

void inserareLaInceput(struct Nod** cap, struct Meniu meniu) {

	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
	nou->info = meniu;
	nou->next = *cap;
	*cap = nou;
}

void afisareMeniu(struct Meniu meniu) {
	printf("Meniul %s are pretul %d \n", meniu.denumire, meniu.pret);
}

void afisareMeniuri(struct Nod* cap) {
	while (cap) {
		afisareMeniu(cap->info);
		cap = cap->next;
	}
}

void dezalocareLista(struct Nod** cap) {

	while (*cap)
	{
		free((*cap)->info.denumire);
		struct Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}
}

int main()
{
	struct Nod* cap = NULL;

	inserareLaInceput(&cap, creareMeniu(30, "Pizza"));
	inserareLaInceput(&cap, creareMeniu(20, "Paste"));
	inserareLaInceput(&cap, creareMeniu(25, "Salate"));

	afisareMeniuri(cap);
	dezalocareLista(&cap);
	afisareMeniuri(cap);

	return 0;
}
