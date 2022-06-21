#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct NodGraf NodGraf;
typedef struct Judet Judet;
typedef struct NodLegatura NodLegatura;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;


struct Nod {
	int ID;
	Nod* next;
	Nod* prev;
};
struct ListaDubla {
	Nod* first;
	Nod* last;
};

struct Judet
{
	int id;
	char* nume;
};
struct NodLegatura
{
	NodLegatura* next;
	NodGraf* info;
};
struct NodGraf
{
	Judet info;
	NodGraf* next;
	NodLegatura* legaturi;
};

void push(ListaDubla* ld, int ID) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = ld->first;
	nou->prev = NULL;
	nou->ID = ID;

	if (ld->first == NULL) {
		ld->first = ld->last = nou;
	}
	else {
		ld->first->prev = nou;
		ld->first = nou;
	}
}

void inserareCoada(ListaDubla* ld, int ID) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->prev = ld->last;
	nou->ID = ID;

	if (ld->last == NULL) {
		ld->first = ld->last = nou;
	}
	else {
		ld->last->next = nou;
		ld->last = nou;
	}
}

int pop(ListaDubla* ld) {
	int ID = -1;
	if (ld->first) {
		ID = ld->first->ID;
		Nod* aux = ld->first;
		ld->first = ld->first->next;
		if (ld->first == NULL) {
			ld->last = NULL;
		}
		free(aux);
	}
	return ID;
}

Judet initializaJudet(int id, const char* nume)
{
	Judet j;
	j.id = id;
	j.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(j.nume, nume);

	return j;
}

NodGraf* inserareNodGraf(NodGraf* lista, Judet j)
{
	NodGraf* nou = (NodGraf*)malloc(sizeof(NodGraf));
	nou->info = j;
	nou->legaturi = NULL;
	nou->next = NULL;

	if (lista)
	{
		NodGraf* p = lista;
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
		return lista;
	}
	else return nou;
}

NodLegatura* inserareNodLegatura(NodLegatura* cap, NodGraf* info)
{
	NodLegatura* nou = (NodLegatura*)malloc(sizeof(NodLegatura));
	nou->next = NULL;
	nou->info = info;
	if (cap)
	{
		NodLegatura* p = cap;
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else return nou;
}

void afisareListaP(NodGraf* lista)
{
	NodGraf* p = lista;
	while (p)
	{
		printf("ID: %d, Judet: %s  are legatura directa cu:\n", p->info.id, p->info.nume);
		NodLegatura* leg = p->legaturi;
		while (leg)
		{
			printf("	id: %d , nume: %s\n", leg->info->info.id, leg->info->info.nume);
			leg = leg->next;
		}
		p = p->next;
	}
}

NodGraf* cautareDupaId(NodGraf* lista, int id)
{
	while (lista && lista->info.id != id)
	{
		lista = lista->next;
	}
	return lista;
}
void inserareMuchie(NodGraf* lista, int idStart, int iddDestinatie)
{
	NodGraf* nodStart = cautareDupaId(lista, idStart);
	NodGraf* nodDestinatie = cautareDupaId(lista, iddDestinatie);

	if (nodStart && nodDestinatie)
	{
		nodStart->legaturi = inserareNodLegatura(nodStart->legaturi, nodDestinatie);
		nodDestinatie->legaturi = inserareNodLegatura(nodDestinatie->legaturi, nodStart);
	}
}
int getNumarNoduri(NodGraf* graf) {
	int nr = 0;
	while (graf) {
		nr++;
		graf = graf->next;
	}
	return nr;
}

void parcurgereInAdancime(NodGraf* graf, int idStart) {
	ListaDubla stiva;
	stiva.first = stiva.last = NULL;
	push(&stiva, idStart);
	int nrNoduri = getNumarNoduri(graf);
	int* vizitate = (int*)malloc(sizeof(int) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	vizitate[idStart - 1] = 1;
	while (stiva.first) {
		int idCurent = pop(&stiva);
		NodGraf* nodCurent = cautareDupaId(graf, idCurent);
		printf("%d. Judetul %s. \n", nodCurent->info.id, nodCurent->info.nume);
		NodLegatura* p = nodCurent->legaturi;
		while (p) {
			if (vizitate[p->info->info.id - 1] == 0) {
				push(&stiva, p->info->info.id);
				vizitate[p->info->info.id - 1] = 1;
			}
			p = p->next;
		}

	}
}

void parcurgereInLatime(NodGraf* graf, int idStart) {
	ListaDubla coada;
	coada.first = coada.last = NULL;
	inserareCoada(&coada, idStart);
	int nrNoduri = getNumarNoduri(graf);
	int* vizitate = (int*)malloc(sizeof(int) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	vizitate[idStart - 1] = 1;
	while (coada.first) {
		int idCurent = pop(&coada);
		NodGraf* nodCurent = cautareDupaId(graf, idCurent);
		printf("%d. Judetul %s. \n", nodCurent->info.id, nodCurent->info.nume);
		NodLegatura* p = nodCurent->legaturi;
		while (p) {
			if (vizitate[p->info->info.id - 1] == 0) {
				inserareCoada(&coada, p->info->info.id);
				vizitate[p->info->info.id - 1] = 1;
			}
			p = p->next;
		}

	}
}

void main()
{
	NodGraf* graf = NULL;
	graf = inserareNodGraf(graf, initializaJudet(1, "Bucuresti"));
	graf = inserareNodGraf(graf, initializaJudet(2, "Iasi"));
	graf = inserareNodGraf(graf, initializaJudet(3, "Brasov"));
	graf = inserareNodGraf(graf, initializaJudet(4, "Vaslui"));
	graf = inserareNodGraf(graf, initializaJudet(5, "Cluj"));
	graf = inserareNodGraf(graf, initializaJudet(6, "Botosani"));

	afisareListaP(graf);
	inserareMuchie(graf, 1, 3);
	inserareMuchie(graf, 1, 5);
	inserareMuchie(graf, 1, 6);
	inserareMuchie(graf, 2, 3);
	inserareMuchie(graf, 3, 4);
	inserareMuchie(graf, 5, 4);
	inserareMuchie(graf, 5, 6);
	inserareMuchie(graf, 6, 4);

	printf("\n");
	afisareListaP(graf);
	printf("\n\nParcurgere in adancime:\n");
	parcurgereInAdancime(graf, 1);
	printf("\n\nParcurgere in latime:\n");
	parcurgereInLatime(graf, 1);

}