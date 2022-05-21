#include<stdio.h>
#include<malloc.h>

typedef struct Sport Sport;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct Sport {
	int id;
	char* denumire;
	float buget;
};

struct NodPrincipal {
	Sport info;
	NodPrincipal* next;
	NodSecundar* vecini;

};

struct NodSecundar {
	NodPrincipal* info;
	NodSecundar* next;
};

Sport initializareSport(int id, char* denumire, float buget) {
	Sport sport;
	sport.id = id;
	sport.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(sport.denumire, denumire);
	sport.buget = buget;
	return sport;
}

void inserareFinal(Sport sport, NodPrincipal** cap) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = sport;
	nou->next = NULL;
	nou->vecini = NULL;

	if (*cap) {
		NodPrincipal* aux = (*cap);
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	} else{
		*cap = nou;
	}
}

void inserareInListaSecundara(NodSecundar** capSecund, NodPrincipal* nodPrincipalInfoUtila) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->info = nodPrincipalInfoUtila;
	nou->next = NULL;
	if (*capSecund) {
		NodSecundar* aux = (*capSecund);
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		(*capSecund) = nou;
	}
}

void afisare(NodPrincipal* cap) {
	while (cap) {
		printf("%d, denumire: %s, buget: %f\n", cap->info.id, cap->info.denumire, cap->info.buget);
		NodSecundar* aux = cap->vecini;
		while (aux) {
			printf("Vecin: %d, denumire: %s, buget: %f\n", aux->info->info.id, aux->info->info.denumire, aux->info->info.buget);
			aux = aux->next;
		}
		cap = cap->next;
	}
}

NodPrincipal* cautareId(NodPrincipal* nod, int id)
{
	while (nod && nod->info.id != id)
	{
		nod = nod->next;
	}
	return nod;
}

void inserareVecini(NodPrincipal* nod, int id1, int id2)
{
	NodPrincipal* nodCautat1= cautareId(nod, id1);
	NodPrincipal* nodCautat2 = cautareId(nod, id2);
	if (nodCautat1 && nodCautat2)
	{
		inserareInListaSecundara(&nodCautat1->vecini, nodCautat2);
		inserareInListaSecundara(&nodCautat2->vecini, nodCautat1);
	}
	
}

void main() {
	NodPrincipal* capPrincipal = NULL;

	inserareFinal(initializareSport(1, "Fotbal", 100000), &capPrincipal);
	inserareFinal(initializareSport(2, "Baschet", 200000), &capPrincipal);
	inserareFinal(initializareSport(3, "Handbal", 300000), &capPrincipal);
	inserareFinal(initializareSport(4, "Volei", 1000100), &capPrincipal);
	inserareFinal(initializareSport(5, "Golf", 220000), &capPrincipal);

	inserareVecini(capPrincipal, 1, 2);
	inserareVecini(capPrincipal, 1, 4);
	inserareVecini(capPrincipal, 1, 5);
	inserareVecini(capPrincipal, 2, 4);
	inserareVecini(capPrincipal, 3, 5);

	afisare(capPrincipal);
}
