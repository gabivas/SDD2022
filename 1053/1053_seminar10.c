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

void afisarePOSTORDINE(Nod* rad)
{
	if (rad)
	{
		afisarePOSTORDINE(rad->st);
		afisarePOSTORDINE(rad->dr);
		afisare(rad->info);
	}
}

Film cautareNod(Nod* rad, int id)
{
	if (rad != NULL)
	{
		if (rad->info.id == id)
		{
			return initializareFilm(rad->info.id, rad->info.nume, rad->info.rating);
		}
		else
		{
			if (id > rad->info.id)
			{
				return cautareNod(rad->dr, id);
			}
			else
			{
				return cautareNod(rad->st, id);
			}
		}
	}
	else
	{
		return initializareFilm(-1, "NULL", -1);
	}
}

void stergereArbore(Nod** rad)
{
	if ((*rad) != NULL)
	{
		stergereArbore(&(*rad)->st);
		stergereArbore(&(*rad)->dr);
		free((*rad)->info.nume);
		free(*rad);
	}
	*rad = NULL;
}

int inaltimeArbore(Nod* rad)
{
	if (rad)
	{
		if (inaltimeArbore(rad->st) < inaltimeArbore(rad->dr))
		{
			return inaltimeArbore(rad->dr) + 1;
		}
		else
		{
			return inaltimeArbore(rad->st) + 1;
		}

	}
	else
	{
		return 0;
	}
}

int diferentaInaltimi(Nod* rad)
{
	if (rad)
	{
		return inaltimeArbore(rad->st) - inaltimeArbore(rad->dr);
	}
	else return 0;
}

void rotire_la_stanga(Nod** rad)
{
	Nod* aux = (*rad)->dr;
	(*rad)->dr = aux->st;
	aux->st = (*rad);
	*rad = aux;

}

void rotire_la_dreapta(Nod** rad)
{
	Nod* aux = (*rad)->st;
	(*rad)->st = aux->dr;
	aux->dr = (*rad);
	*rad = aux;

}

void inserareAVL(Nod** rad, Film f)
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
			inserareAVL(&(*rad)->dr, f);
		}
		else
		{
			inserareAVL(&(*rad)->st, f);
		}
		int diferenta_inaltime = diferentaInaltimi(*rad);
		if (diferenta_inaltime == 2)
		{
			if (diferentaInaltimi((*rad)->st) == -1)
			{
				rotire_la_stanga(&(*rad)->st);
				rotire_la_dreapta(rad);
			}
			else
			{
				rotire_la_dreapta(rad);
			}
		}
		else if (diferenta_inaltime == -2)
		{
			if (diferentaInaltimi((*rad)->dr) == 1)
			{
				rotire_la_dreapta(&(*rad)->dr);
				rotire_la_stanga(rad);
			}
			else {
				rotire_la_stanga(rad);

			}
		}
	}
}

void main() {

	Nod* rad = NULL;

	inserareAVL(&rad, initializareFilm(1, "Batman", 8));
	inserareAVL(&rad, initializareFilm(2, "Captain America ", 9));
	inserareAVL(&rad, initializareFilm(3, "Star Wars ", 6.97));
	inserareAVL(&rad, initializareFilm(4, "Suicide Squad", 10));
	inserareAVL(&rad, initializareFilm(5, "Interstelar", 10));

	afisareINORDINE(rad);
}