#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct Masina
{
	char* marca;
	int nrKm;
	float consum;
};

struct Masina citireMasinaFisier(FILE* streamFisier) {
    if (streamFisier != NULL) {
        struct Masina masina;
        char aux[30];
        fscanf(streamFisier, "%29s", aux);
        masina.marca = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
        strcpy(masina.marca, aux);
        fscanf(streamFisier, "%d", &masina.nrKm);
        fscanf(streamFisier, "%f", &masina.consum);

        return masina;
    }
}
struct Masina* citireMasiniFisier(FILE* streamFisier, int* nrMasini)
{
	if (streamFisier != NULL)
	{
        fscanf(streamFisier, "%d", nrMasini);
		struct Masina* vectorMasini = (struct Masina*)malloc(sizeof(struct Masina) * (*nrMasini));
		for (int i = 0; i < *nrMasini; i++)
		{
			vectorMasini[i] = citireMasinaFisier(streamFisier);
		}

		return vectorMasini;
	}
}

struct Masina** citireMatriceMasiniFisier(char* numeFisier, int* nrLinii, int** vectorNrMasiniPeLinie)
{
	FILE* streamFisier = fopen(numeFisier, "r");
	if (streamFisier != NULL)
	{
        fscanf(streamFisier, "%d", nrLinii);
		struct Masina** matriceMasini = (struct Masina**)malloc(sizeof(struct Masina*) * (*nrLinii));
		*vectorNrMasiniPeLinie = (int*)malloc(sizeof(int) * (*nrLinii));
		for (int i = 0; i < *nrLinii; i++)
		{
			matriceMasini[i] = citireMasiniFisier(streamFisier, &((*vectorNrMasiniPeLinie)[i]));
		}

		return matriceMasini;
	}
}

void citireMatriceMasiniFisier2(struct Masina*** matriceMasini, char* numeFisier, int* nrLinii, int** vectorNrMasiniPeLinie)
{
	FILE* streamFisier = fopen(numeFisier, "r");
	if (streamFisier != NULL)
	{
        fscanf(streamFisier, "%d", nrLinii);
		(*matriceMasini) = (struct Masina**)malloc(sizeof(struct Masina*) * (*nrLinii));
		*vectorNrMasiniPeLinie = (int*)malloc(sizeof(int) * (*nrLinii));
		for (int i = 0; i < *nrLinii; i++)
		{
			(*matriceMasini)[i] = citireMasiniFisier(streamFisier, &((*vectorNrMasiniPeLinie)[i]));
		}
	}
}

void afisareMasina(struct Masina masina)
{
	printf("%s %d %.2f\n", masina.marca, masina.nrKm, masina.consum);
}

void afisareMatriceMasini(struct Masina** matriceMasini, int nrLinii, int* vectorNrMasiniPeLinie)
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < vectorNrMasiniPeLinie[i]; j++)
		{
			afisareMasina(matriceMasini[i][j]);

		}
	}
}

void citireMasinaTastatura(struct Masina* masina)
{
    printf("Citire masina: ");
    *masina = citireMasinaFisier(stdin);
}

void dezalocareMatriceMasini(struct Masina*** matriceMasini, int* nrLinii, int** vectorNrMasiniPeLinie)
{
	for (int i = 0; i < *nrLinii; i++)
	{
		for (int j = 0; j < (*vectorNrMasiniPeLinie)[i]; j++)
		{
			free((*matriceMasini)[i][j].marca);
		}
		free((*matriceMasini)[i]);
	}
	free(*matriceMasini);
	free(*vectorNrMasiniPeLinie);
	*matriceMasini = NULL;
	*vectorNrMasiniPeLinie = NULL;
	*nrLinii = 0;
}

float consumMediu(struct Masina** matriceMasini, int nrLinii, int* vectorNrMasiniPeLinie)
{
	int nrMasini = 0;
	float consumTotal = 0;
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < vectorNrMasiniPeLinie[i]; j++)
		{
			nrMasini++;
			consumTotal += matriceMasini[i][j].consum;
		}
	}
	if (nrMasini != 0)
		return consumTotal / nrMasini;
	else
		return 0;
}

int main()
{
	/*struct Masina m;
	citireMasinaTastatura(&m);
	afisareMasina(m);*/

	struct Masina** matriceMasini;
	int nrlinii, *vectorNrMasiniPeLinie;
	//m = citireMatriceMasini("Masini.txt", &nrlinii, &nrmasini);
	citireMatriceMasiniFisier2(&matriceMasini, "MatriceMasini_Seminar3.txt", &nrlinii, &vectorNrMasiniPeLinie);
	afisareMatriceMasini(matriceMasini, nrlinii, vectorNrMasiniPeLinie);
	float consummediu = consumMediu(matriceMasini, nrlinii, vectorNrMasiniPeLinie);
	printf("%.2f", consummediu);
	dezalocareMatriceMasini(&matriceMasini, &nrlinii, &vectorNrMasiniPeLinie);

}