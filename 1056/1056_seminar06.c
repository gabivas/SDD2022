#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Nod Nod;
typedef struct LD LD;
typedef struct Fruct Fruct;

struct Fruct {
	char* denumire;
	int calorii;
};

struct Nod {
	Nod* prev;
	Nod* next;
	Fruct inf;
};

struct LD {
	Nod* prim;
	Nod* ultim;
};

Fruct creareFruct(const char* denumire, int calorii) {
	Fruct fruct;
	fruct.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy_s(fruct.denumire, strlen(denumire) + 1, denumire);

	fruct.calorii = calorii;

	return fruct;
}

void afisareFruct(Fruct fruct) {
	printf("fructul %s are %d calorii\n", fruct.denumire, fruct.calorii);
}

void inserareInceput(Fruct fruct, LD* listaDubla) {
	Nod* n = (Nod*)malloc(sizeof(Nod));

	n->inf = fruct;
	n->prev = NULL;
	n->next = listaDubla->prim;

	if (listaDubla->prim) {
		listaDubla->prim->prev = n;
		listaDubla->prim = n;
	}
	else {
		listaDubla->prim = n;
		listaDubla->ultim = n;
	}
}

void inserareFinal(Fruct fruct, LD* listaDubla)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = fruct;
	nou->next = NULL;
	nou->prev = listaDubla->ultim;
	if (listaDubla->ultim)
	{
		listaDubla->ultim->next = nou;
		listaDubla->ultim = nou;
	}
	else
	{
		listaDubla->prim = listaDubla->ultim = nou;
	}
}

void afisareStangaDreapta(LD listaDubla)
{
	Nod* aux = listaDubla.prim;
	while (aux)
	{
		afisareFruct(aux->inf);
		aux = aux->next;
	}
}

void afisareDreaptaStanga(LD listaDubla) {
	Nod* aux = listaDubla.ultim;
	while (aux) {
		afisareFruct(aux->inf);
		aux = aux->prev;
	}
}

void afisareListaDublaCirculara(struct LD listaDubla) {
	struct Nod* aux;
	aux = listaDubla.ultim->next;

	do
	{
		afisareFruct(aux->inf);
		aux = aux->next;

	} while (aux != listaDubla.ultim->next);
}

void stergeLista(LD* listaDubla) {
	Nod* aux = listaDubla->ultim;
	while (aux) {
		free(aux->inf.denumire);
		aux = aux->prev;
		if (aux) {
			free(aux->next);
		}
	}
	free(listaDubla->prim);

	listaDubla->prim = NULL;
	listaDubla->ultim = NULL;
}

void conversieListaVector(LD listaDubla, Fruct** vector, int* nrFructe)
{
	Nod* temp = listaDubla.prim;
	while (temp)
	{
		(*vector)[*nrFructe] = creareFruct(temp->inf.denumire, temp->inf.calorii);
		(*nrFructe)++;
		temp = temp->next;
	}
}

int main() {
	LD listad, listad2;
	listad.prim = NULL;
	listad.ultim = NULL;
	listad2.prim = NULL;
	listad2.ultim = NULL;

	inserareInceput(creareFruct("avocado", 200), &listad);
	inserareInceput(creareFruct("mar", 100), &listad);
	inserareInceput(creareFruct("capsuni", 150), &listad);

	inserareFinal(creareFruct("avocado", 200), &listad2);
	inserareFinal(creareFruct("mar", 100), &listad2);
	inserareFinal(creareFruct("capsuni", 150), &listad2);

	//listad2.prim->prev = listad2.ultim;
	//listad2.ultim->next = listad2.prim;
	//afisareListaDublaCirculara(listad2);

	afisareStangaDreapta(listad);
	printf("-----\n");
	afisareStangaDreapta(listad2);

	printf("\nafisare inversa\n\n");
	afisareDreaptaStanga(listad);
	printf("-----\n");
	afisareDreaptaStanga(listad2);

	Fruct* vector = (Fruct*)malloc(sizeof(Fruct) * 3);
	int nrFructe = 0;
	conversieListaVector(listad, &vector, &nrFructe);

	printf("\nAfisare vector\n\n");
	for (int i = 0; i < nrFructe; i++)
	{
		afisareFruct(vector[i]);
	}
	stergeLista(&listad);
	stergeLista(&listad2);


	return 0;

}