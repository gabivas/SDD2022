#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

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
	

	if ((*rad)==NULL)
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

void main() {

	Nod* radacina = NULL;
	inserareArbore(initializarefilm(6, "Godfather", 9.9), &radacina);
	inserareArbore(initializarefilm(8, "Cars", 6.9), &radacina);
	inserareArbore(initializarefilm(3, "Cars II", 5.9), &radacina);
	inserareArbore(initializarefilm(4, "Godfather II", 8.9), &radacina);
	inserareArbore(initializarefilm(9, "Godfather III", 7.5), &radacina);
	inserareArbore(initializarefilm(2, "Tom & Jerry ", 10), &radacina);
	
	parcurgereInordine(radacina);
	printf("\n");
	parcurgerePreordine(radacina);
	
	Film f;
	f = cautare(10, radacina);
	printf("--------------------\n");
	afisareFilm(f);
	free(f.titlu);
	inserareArbore(initializarefilm(1, "Godfather III", 7.5), &radacina);
	printf("%d", calculInaltime(radacina));
	dezalocare(&radacina);
	parcurgereInordine(radacina);
}