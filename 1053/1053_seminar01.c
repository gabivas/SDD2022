#include <stdio.h>
#include< malloc.h>
void interschimbareNumereIntregi(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void citireVectorTastatura(int** vector, int* nrElemente)
{
	scanf_s("%d", nrElemente);
	*vector = (int*)malloc((*nrElemente) * sizeof(int));
	for (int i = 0; i < (*nrElemente); i++)
	{
		//scanf_s("%d", &(*v)[i]);
		scanf_s("%d", (*vector) + i);
	}
}
void main()
{
	int x = 100;
	float y = 23.4;
	char z = 'a';
	double a = 23.5748;
	//printf("%c", z);
	printf("%c, %d, %5.1f, %lf", z, x, y, a);
	printf("\n");
	z++;
	printf("%c\n", z);
	printf("%d\n", z);


	char sir[4] = "abc";
	//sir[3] = 0;
	printf("%s\n", sir);
	char* sir2 = malloc(4 * sizeof(char));
	sir2[0] = 97;
	sir2[1] = 98;
	sir2[2] = 99;
	sir2[3] = 0;
	printf("%s\n", sir2);
	int val1 = 2, val2 = 5;
	interschimbareNumereIntregi(&val1, &val2);
	printf("%d, %d\n", val1, val2);
	int nrElem;
	int* vector;

	citireVectorTastatura(&vector, &nrElem);
	for (int i = 0; i < nrElem; i++)
	{
		printf("%d ", vector[i]);
	}


}