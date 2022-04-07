#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Carte Carte;
typedef struct Nod Nod;

struct Carte {
	char* nume_carte;
	long id;
};
struct Nod {
	Nod* next;
	Carte info;
};

Carte initializareCarte(char* nume, long id_carte)
{	Carte carte;
	carte.nume_carte = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(carte.nume_carte, nume);
	carte.id = id_carte;

	return carte;
}

Carte initializareCarteFaraParam()
{
	Carte carte;

	carte.nume_carte = NULL;
	carte.id = -1;

	return carte;
}

void afisareCarte(Carte carte) {
	if (carte.nume_carte) {
	printf("Cartea %s cu id-ul %ld \n", carte.nume_carte, carte.id);
}
}

void push(Carte carte, Nod** varf) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carte;

	nou->next = *varf;
	*varf = nou;
}

Carte pop(Nod** varf) {
	Carte carte;
	if (*varf) {
		carte = (*varf)->info;
		Nod* aux = *varf;
		*varf = (*varf)->next;
		free(aux);
	}
	else {
		carte.nume_carte = NULL;
		carte.id = -1;
	}

	return carte;
}

void put(Carte carte, Nod** prim) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carte;
	nou->next = NULL;
	Nod* aux = *prim;

	if (aux) {
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
	{
		*prim = nou;
	}
}

Carte cautareCarteDupaID(Nod** varf, long id) {
	Carte carte= initializareCarteFaraParam();
	Nod* stivaAux = NULL;

	while ((*varf) != NULL && (*varf)->info.id != id) {
		push(pop(varf), &stivaAux);
	}
	if ((*varf) != NULL)
	{
		carte = pop(varf);
	}
	while (stivaAux != NULL) {
		push(pop(&stivaAux), varf);
	}

	return carte;
}

int main()
{
	Nod* stiva = NULL;
	push(initializareCarte("Ion", 320323), &stiva);
	push(initializareCarte("The Last Wish", 3230323), &stiva);
	push(initializareCarte("Time of contempt", 3260323), &stiva);

	printf("Cartea cautata:\n");
	afisareCarte(cautareCarteDupaID(&stiva, 32303233));
	printf("\n\n");

	Carte c;
	while (stiva != NULL) {
		c = pop(&stiva);
		afisareCarte(c);
		free(c.nume_carte);
	}
	printf("\n\n");

	Nod* coada = NULL;
	put(initializareCarte("Ion", 320323), &coada);
	put(initializareCarte("The Last Wish", 3230323), &coada);
	put(initializareCarte("Time of contempt", 3260323), &coada);

	while (coada != NULL) {
		c = pop(&coada);
		afisareCarte(c);
		free(c.nume_carte);
	}

	return 0;
}