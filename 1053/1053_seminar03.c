#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

struct Student {
	char* nume;
	int varsta;
	float medie;
};

struct Student citireStudent(FILE* streamFisier) {
	struct Student student;
	if (streamFisier != NULL)
	{
		char buffer[20];
		fgets(buffer, 20, streamFisier);
		char* sir = strtok(buffer, "\n");
		student.nume = (char*)malloc(sizeof(char) * (strlen(sir) + 1));
		strcpy(student.nume, sir);
		fgets(buffer, 4, streamFisier);
		student.varsta = atoi(buffer);
		fgets(buffer, 10, streamFisier);
		student.medie = atof(buffer);
	}
	return student;
}

struct Student* citireVectorStudenti(FILE* streamFisier, int* nrStudenti) {
	if (streamFisier != NULL)
	{
		char buffer[10];
		fgets(buffer, 3, streamFisier);
		*nrStudenti = atoi(buffer);
		struct Student* vectorStudenti = (struct Student*)malloc(sizeof(struct Student) * (*nrStudenti));
		for (int i = 0; i < (*nrStudenti); i++)
			vectorStudenti[i] = citireStudent(streamFisier);

		return vectorStudenti;
	}
}

struct Student** citireMatriceStudenti(char* numeFisier, int* nrLinii, int** vectorNrStudentiPeLinie) {
	FILE* streamFisier = fopen(numeFisier, "r");
	char buffer[10];
	fgets(buffer, 10, streamFisier);
	*nrLinii = atoi(buffer);
	*vectorNrStudentiPeLinie = (int*)malloc(sizeof(int) * (*nrLinii));
	struct Student** matriceStudenti = (struct Student**)malloc(sizeof(struct Student*) * (*nrLinii));
	for (int i = 0; i < (*nrLinii); i++)
		matriceStudenti[i] = citireVectorStudenti(streamFisier, &((*vectorNrStudentiPeLinie)[i]));

	return matriceStudenti;

}


struct Student citireStudentTastatura() {
	struct Student student;
	printf("Citire student: ");
	char buffer[20];

	scanf("%s", &buffer);
	student.nume = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(student.nume, buffer);
	scanf("%d", &student.varsta);
	scanf("%f", &student.medie);

	return student;
}

void afisareStudent(struct Student student)
{
	printf("%s", student.nume);
	printf("\n%d", student.varsta);
	printf("\n%.2f", student.medie);
}

void afisareMatriceStudenti(struct Student** matriceStudenti, int nrLinii, int* vectorNrStudentiPeLinie)
{
	for (int i = 0; i < nrLinii; i++)
		for (int j = 0; j < vectorNrStudentiPeLinie[i]; j++) {
			afisareStudent(matriceStudenti[i][j]);
			printf("\n");
		}
}

int main()
{
	//FILE* g = fopen("MatriceStudenti_Seminar3.txt", "r");
	//struct Student s = citireStudent(g);
	//afisareStudent(s);
	//vector de studenti,ne folosim de citire student
	//citireStudenti care returneaza un vector de studenti + dezalocare
	//printf("\n");
	//struct Student s2 = citireStudentTastatura();
	//afisareStudent(s2);
	//free(s.nume);
	/*struct Student* vs;
	int n;
	vs = citireVectorStudenti(g, &n);
	for (int i = 0; i < n; i++)
		afisareStudent(vs[i]);*/
	int nrLinii = 0, * vectorNrStudentiPeLinie = NULL;
	struct Student** matriceStudenti = citireMatriceStudenti("MatriceStudenti_Seminar3.txt", &nrLinii, &vectorNrStudentiPeLinie);
	afisareMatriceStudenti(matriceStudenti, nrLinii, vectorNrStudentiPeLinie);

	return 0;
}