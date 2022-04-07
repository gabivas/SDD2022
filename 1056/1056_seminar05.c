#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Telefon Telefon;
typedef struct Nod Nod;

struct Telefon {
	long id;
	char* marca;
	float pret;
};

struct Nod {
	Telefon inf;
	Nod* next;
};

Telefon creareTelefon(long id, char* marca, float pret) {
	Telefon telefon;
	telefon.id = id;
	telefon.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
	strcpy(telefon.marca, marca);
	telefon.pret = pret;

	return telefon;
}

Telefon creareTelefonFaraParam() {
	Telefon telefon;

	telefon.id = -1;
	telefon.marca = NULL;
	telefon.pret = 0;

	return telefon;
}

void afisareTelefon(Telefon telefon) {
	printf("Telefonul cu id: %ld, marca %s are pretul %.2f \n", telefon.id, telefon.marca, telefon.pret);
}

void push(Nod** varf, Telefon telefon)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = telefon;
	nou->next = (*varf);
	(*varf) = nou;

}

Telefon pop(Nod** varf)
{
	Telefon telefon;
	if ((*varf) != NULL) {
		telefon = (*varf)->inf;
		Nod* aux = (*varf);
		(*varf) = (*varf)->next;
		free(aux);
	}
	else {
		telefon.marca = NULL;
		telefon.id = -1;
		telefon.pret = 0;

	}

	return telefon;
}

void put(Nod** prim, Telefon telefon)
{
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->inf = telefon;

	Nod* aux = *prim;
	if (aux)
	{
		while (aux->next)
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

Telefon cautareTelefon(Nod** varf, long id) {
	Telefon telefon = creareTelefonFaraParam();
	Nod* stivaAux = NULL;
	while ((*varf) != NULL && id != (*varf)->inf.id) {
		push(&stivaAux, pop(varf));
	}
	if ((*varf) != NULL) {
		telefon = pop(varf);
	}
	while (stivaAux) {
		push(varf, pop(&stivaAux));
	}

	return telefon;
}

int main() {

	Nod* stiva = NULL;
	Nod* coada = NULL;
	Telefon telefon;
	push(&stiva, creareTelefon(100, "Samsung", 2500));
	push(&stiva, creareTelefon(200, "Apple", 4500));
	push(&stiva, creareTelefon(300, "Xiaomi", 2000));

	Telefon t2 = cautareTelefon(&stiva, 400);
	if (t2.marca != NULL) {
		afisareTelefon(t2);
	}

	printf("\nStiva:\n");
	while (stiva)
	{
		telefon = pop(&stiva);
		afisareTelefon(telefon);
		free(telefon.marca);
	}

	printf("\nCoada:\n");
	put(&coada, creareTelefon(100, "Samsung", 2500));
	put(&coada, creareTelefon(200, "Apple", 2500));
	put(&coada, creareTelefon(300, "Xiaomi", 2500));

	while (coada)
	{
		telefon = pop(&coada);
		afisareTelefon(telefon);
		free(telefon.marca);
	}

	return 0;

}