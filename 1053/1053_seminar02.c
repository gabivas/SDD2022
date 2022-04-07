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

void citireVectorFisier(FILE* streamFisier, int* nrElem, int** vector)
{
	if (streamFisier != NULL)
	{
		fscanf(streamFisier, "%d", nrElem);
		*vector = (int*)malloc(sizeof(int) * (*nrElem));
		for (int i = 0; i < *nrElem; i++)
		{
			fscanf(streamFisier, "%d", (*vector) + i);
		}
	}
}

struct Student citireStudentFisier(FILE* streamFisier) {
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

void afisareStudent(struct Student s)
{
	printf("%s", s.nume);
	printf("\n%d", s.varsta);
	printf("\n%.2f", s.medie);
}

int main()
{
	//FILE* f = NULL;
	//fopen_s(&f,"FisierNumereIntregi_Seminar2.txt", "r");
	FILE* f = fopen("FisierNumereIntregi_Seminar2.txt", "r");
	//int a, b;
	//if (f != NULL) {
		//fscanf_s(f, "%d", &a);
		//fscanf_s(f, "%d", &b);
		//fscanf(f, "%d", &a);
		//fscanf(f, "%d", &b);
	//}
	//fclose(f);
	//printf("%d,%d", a, b);
	int nrElem;
	int* vector;
	citireVectorFisier(f, &nrElem, &vector);

	printf("%d\n", nrElem);
	for (int i = 0; i < nrElem; i++)
		printf("%d ", vector[i]);

	FILE* g = fopen("Student_Seminar2.txt", "r");
	struct Student s = citireStudentFisier(g);

	printf("\nAfisare student:\n");
	afisareStudent(s);

	free(s.nume);

	return 0;

}