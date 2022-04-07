#include<stdio.h>
#include<malloc.h>

typedef struct Produs Produs;
typedef struct Nod Nod;
typedef struct LD LD;

struct Produs {
	char* denumire_produs;
	float pret;
};

struct Nod {
	Produs info;
	Nod* next;
	Nod* prev;
};

struct LD {
	Nod* prim;
	Nod* ultim;
};

void afisareProdus(Produs produs) {
	printf("Magazinul are produsul %s cu pretul %.2f\n", produs.denumire_produs, produs.pret);
}

Produs initializareProdus(char* denumire_produs, float pret) {
	Produs produs;
	produs.denumire_produs = (char*)malloc(sizeof(char) * (strlen(denumire_produs) + 1));
	strcpy(produs.denumire_produs, denumire_produs);
	produs.pret = pret;

	return produs;
}

void inserareInceput(Produs produs, LD* lista)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = produs;
	nou->prev = NULL;
	nou->next = lista->prim;

	if (lista->prim) {
		lista->prim->prev = nou;
		lista->prim = nou;
	}
	else {
		lista->prim = nou;
		lista->ultim = nou;
	}
}

void traversareStangaDreaptaLista(LD lista) {
	Nod* aux = lista.prim;
	while (aux != NULL) {
		afisareProdus(aux->info);
		aux = aux->next;
	}

}

void traversareDreaptaStangaLista(LD lista) {
	Nod* aux = lista.ultim;
	while (aux != NULL) {
		afisareProdus(aux->info);
		aux = aux->prev;
	}
}

void traversareListaDublaCirculara(struct LD lista) {
	struct Nod* p;
	p = lista.ultim->next;

	do
	{
		afisareProdus(p->info);
		p = p->next;

	} while (p != lista.ultim->next);
}

void inserareSfarsit(Produs p, LD* lista) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = p;
	nou->prev = lista->ultim;
	nou->next = NULL;

	if (lista->ultim)
	{
		lista->ultim->next = nou;
		lista->ultim = nou;
	}
	else
	{
		lista->prim = nou;
		lista->ultim = nou;
	}

}

void conversieListaVector(LD lista, Produs** vector, int* nrProduse) {
	Nod* aux = lista.prim;
	while (aux) {
		(*vector)[*nrProduse] = initializareProdus(aux->info.denumire_produs, aux->info.pret);
		(*nrProduse)++;
		aux = aux->next;
	}

}

int main() {
	LD lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	inserareInceput(initializareProdus("Lapte", 10), &lista);
	inserareInceput(initializareProdus("Cereale", 15), &lista);
	inserareInceput(initializareProdus("Scortisoara", 7), &lista);

	//lista.prim->prev = lista.ultim;
	//lista.ultim->next= lista.prim;
	//traversareListaDublaCirculara(lista);

	LD lista2;
	lista2.prim = NULL;
	lista2.ultim = NULL;
	inserareSfarsit(initializareProdus("Lapte", 10), &lista2);
	inserareSfarsit(initializareProdus("Cereale", 15), &lista2);
	inserareSfarsit(initializareProdus("Scortisoara", 7), &lista2);

	traversareStangaDreaptaLista(lista2);
	printf("\n");
	traversareDreaptaStangaLista(lista2);

	printf("\n\n");
	traversareStangaDreaptaLista(lista);
	printf("\n");
	traversareDreaptaStangaLista(lista);

	int nrProduseLista = 3;
	int nrProduse = 0;
	Produs* vector = (Produs*)malloc(sizeof(Produs) * nrProduseLista);
	conversieListaVector(lista2, &vector, &nrProduse);

	printf("\n\n");
	for (int i = 0; i < nrProduse; i++)
	{
		afisareProdus(vector[i]);
	}

	return 0;
}