#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Masina {
	char* marca;
	int nrkm;
	float consum;
};

struct Masina citireMasinaFisier(FILE* streamFisier) {
	if (streamFisier != NULL) {
		struct Masina masina;
		char aux[30];
		fgets(aux, 30, streamFisier);
		char* sir = strtok(aux, "\n");
		masina.marca = (char*)malloc(sizeof(char) * (strlen(sir) + 1));
		strcpy(masina.marca, sir);

		fgets(aux, 10, streamFisier);
		masina.nrkm = atoi(aux);

		fgets(aux, 10, streamFisier);
		masina.consum = atof(aux);

		return masina;
	}
}

struct Masina* citireMasiniFisier(FILE* streamFisier, int* nrMasini) {
	if (streamFisier != NULL) {
		char aux[30];
		fgets(aux, 3, streamFisier);
		(*nrMasini) = atoi(aux);
		struct Masina* vectorMasini = (struct Masina*)malloc((*nrMasini) * sizeof(struct Masina));
		for (int i = 0; i < (*nrMasini); i++) {
			vectorMasini[i] = citireMasinaFisier(streamFisier);
		}

		return vectorMasini;
	}
}

void afisareMasina(struct Masina masina) {
	printf("%s  %d  %.2f", masina.marca, masina.nrkm, masina.consum);
}

void citireVectorIntregiFisier(FILE* streamFisier, int* nrElemente, int** vector) {
	if (streamFisier != NULL) {
		fscanf(streamFisier, "%d", nrElemente);
		*vector = (int*)malloc((*nrElemente) * sizeof(int));
		for (int i = 0; i < (*nrElemente); i++) {
			fscanf(streamFisier, "%d", (*vector) + i);
		}
	}
}

int main() {
	/*FILE* f = NULL;
	f= fopen("date.txt", "r");
	int a, b;
	if (f != NULL) {
		fscanf(f, "%d", &a);
		fscanf(f, "%d", &b);
		printf("a= %d \nb= %d \n", a, b);
		fclose(f);
	}
	else {
		printf("Fisierul nu s-a putut deschie !\n");
	}*/

	FILE* h = NULL;
	h = fopen("Date_Seminar2.txt", "r");
	int nrElem;
	int* vect;
	citireVectorIntregiFisier(h, &nrElem, &vect);

	for (int i = 0; i < nrElem; i++) {
		printf("%d\t", vect[i]);
	}

	FILE* g = NULL;
	g = fopen("Masina_Seminar2.txt", "r");

	struct Masina m1;
	m1 = citireMasinaFisier(g);

	printf("\nAfisare masina:\n");
	afisareMasina(m1);

	FILE* f = NULL;
	f = fopen("VectorMasini_Seminar2.txt", "r");
	int nrMasini;
	struct Masina* vectorMasini;
	vectorMasini = citireMasiniFisier(f, &nrMasini);

	printf("\nAfisare vector masini:\n");
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(vectorMasini[i]);
		printf("\n");
	}

	for (int i = 0; i < nrMasini; i++) {
		free(vectorMasini[i].marca);
	}
	free(vectorMasini);
	fclose(f);
	fclose(g);
	fclose(h);

	return 0;
}

