#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>

typedef struct Film Film;
typedef struct Nod Nod;

struct Film {
	int id;
	char* titlu;
	float rating;
};

struct Nod {
	Nod* dreapta;
	Nod* stanga;
	Film inf;
};

Film initializarefilm(int id, char* titlu, float rating) {
	Film f;
	f.id = id;
	f.titlu = (char*)malloc(strlen(titlu) + 1);
	strcpy(f.titlu, titlu);
	f.rating = rating;

	return f;
}

void inserareArbore(Film f, Nod** rad)
{
	if ((*rad) == NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->inf = f;
		nou->dreapta = nou->stanga = NULL;
		*rad = nou;
	}
	else
	{
		if (f.id > (*rad)->inf.id)
		{
			inserareArbore(f, &(*rad)->dreapta);
		}
		else
		{
			inserareArbore(f, &(*rad)->stanga);
		}
	}
}

void afisareFilm(Film f) {
	printf("filmul u id ul %d. se numeste: %s si are un rating de %.2f\n", f.id, f.titlu, f.rating);
}

void parcurgereInordine(Nod* rad) {
	if (rad) {
		parcurgereInordine(rad->stanga);
		afisareFilm(rad->inf);
		parcurgereInordine(rad->dreapta);
	}
}

void parcurgerePreordine(Nod* rad) {
	if (rad) {
		afisareFilm(rad->inf);
		parcurgerePreordine(rad->stanga);
		parcurgerePreordine(rad->dreapta);
	}
}

Film cautare(int id, Nod* rad)
{
	Film f;
	if (rad)
	{
		if (id == rad->inf.id) {
			f = initializarefilm(id, rad->inf.titlu, rad->inf.rating);
			return f;
		}
		else
		{
			if (id > rad->inf.id)
			{
				f = cautare(id, rad->dreapta);
			}
			else
				f = cautare(id, rad->stanga);
			return f;
		}
	}
	else
	{
		f = initializarefilm(-1, "-", -1);
		return f;
	}
}

void dezalocare(Nod** radacina)
{
	if (*radacina != NULL)
	{
		dezalocare(&(*radacina)->stanga);
		dezalocare(&(*radacina)->dreapta);

		free((*radacina)->inf.titlu);
		free(*radacina);
	}
	*radacina = NULL;
}

int calculInaltime(Nod* radacina) {

	if (radacina != NULL) {
		int hdreapta = calculInaltime(radacina->dreapta);
		int hstanga = calculInaltime(radacina->stanga);

		if (hdreapta > hstanga) {
			return hdreapta + 1;
		}
		else {
			return hstanga + 1;
		}
	}
	else {
		return 0;
	}

}

void rotireStanga(Nod** rad)
{
	Nod* aux = (*rad)->dreapta;
	(*rad)->dreapta = aux->stanga;
	aux->stanga = (*rad);

	(*rad) = aux;
}

void rotireDreapta(Nod** rad)
{
	Nod* aux = (*rad)->stanga;
	(*rad)->stanga = aux->dreapta;
	aux->dreapta = (*rad);

	(*rad) = aux;
}

int diferenteInaltimi(Nod* rad)
{
	if (rad)
	{
		int cdreapta = calculInaltime(rad->dreapta);
		int cstanga = calculInaltime(rad->stanga);
		return cstanga - cdreapta;
	}
	return 0;
}

void inserareArboreEchilibrat(Film f, Nod** rad)
{
	if ((*rad) == NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->inf = f;
		nou->dreapta = nou->stanga = NULL;
		*rad = nou;
	}
	else
	{
		if (f.id > (*rad)->inf.id)
		{
			inserareArboreEchilibrat(f, &(*rad)->dreapta);
		}
		else
		{
			inserareArboreEchilibrat(f, &(*rad)->stanga);
		}
	}
	int dif = diferenteInaltimi(*rad);
	if (dif == -2)
	{
		if (diferenteInaltimi((*rad)->dreapta) == 1)
		{
			rotireDreapta(&(*rad)->dreapta);
			rotireStanga(rad);
		}
		else
		{
			rotireStanga(rad);
		}
	}
	if (dif == 2)
	{
		if (diferenteInaltimi((*rad)->stanga) == -1)
		{
			rotireStanga(&(*rad)->stanga);
			rotireDreapta(rad);
		}
		else
		{
			rotireDreapta(rad);
		}
	}
}

void main() {

	Nod* radacina = NULL;

	inserareArboreEchilibrat(initializarefilm(1, "Shrek", 10), &radacina);
	inserareArboreEchilibrat(initializarefilm(2, "Shrek 2", 9), &radacina);
	inserareArboreEchilibrat(initializarefilm(3, "Interstellar", 9.5), &radacina);
	inserareArboreEchilibrat(initializarefilm(4, "Scarface", 9), &radacina);
	inserareArboreEchilibrat(initializarefilm(5, "Doctor Strange", 9), &radacina);

	parcurgereInordine(radacina);

}