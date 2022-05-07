#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <malloc.h>

typedef struct Film Film;
typedef struct Nod Nod;

struct Film
{
	int id;
	char* nume;
	float rating;
};

struct Nod
{
	Film info;
	Nod* dr;
	Nod* st;
};

Film initializareFilm(int id, char* nume, float rating)
{
	Film f;
	f.id = id;
	f.rating = rating;
	f.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(f.nume, nume);
	return f;
}

void inserare(Nod** rad, Film f)
{
	if ((*rad) == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = f;
		nou->dr = nou->st = NULL;
		*rad = nou;						 
	}
	else
	{
		if (f.id > (*rad)->info.id)
		{
			inserare(&(*rad)->dr, f);
		}
		else
		{
			inserare(&(*rad)->st, f);
		}
	}
}

void afisare(Film f) {

	printf("\n#%d Film: %s, rating: %.2f", f.id, f.nume, f.rating);
}

void afisareINORDINE(Nod* rad) {

	if (rad)
	{
		afisareINORDINE(rad->st);
		afisare(rad->info);
		afisareINORDINE(rad->dr);
	}

}

void afisarePREORDINE(Nod* rad)
{
	if (rad)
	{
		afisare(rad->info);
		afisarePREORDINE(rad->st);
		afisarePREORDINE(rad->dr);
	}
}

int main() {
	Nod* rad = NULL;
	inserare(&rad, initializareFilm(5, "Batman", 8));
	inserare(&rad, initializareFilm(3, "Captain America ", 9));
	inserare(&rad, initializareFilm(8, "Star Wars ", 6.97));
	inserare(&rad, initializareFilm(7, "Suicide Squad", 10));
	inserare(&rad, initializareFilm(9, "Interstelar", 10));

	afisareINORDINE(rad);
	printf("\n");
	afisarePREORDINE(rad);

	return 0;
}