#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

void interschimbareNumereIntregi(int* x, int* y) {
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void citireVectorTastatura(int** vector, int* nrElemente) {
	printf("n= ");
	scanf("%d", nrElemente);
	*vector = (int*)malloc((*nrElemente) * sizeof(int));
	for (int i = 0; i < (*nrElemente); i++) {
		printf("v[%d]= ", i);
		scanf("%d", &((*vector)[i]));
	}
}

int main() {
	int a = 10;
	float b = 3.2;
	char c = 'a';

	printf("%c", c);


	c = c + 1;
	printf("\n%c", c);
	printf("\n%d", c);
	printf("\n%i", a);
	printf("\n%f", b);

	char sir[5] = "abcd";
	printf("\n%s", sir);

	char* sir2 = (char*)malloc(5 * sizeof(char));
	sir2[0] = 97;
	sir2[1] = 98;
	sir2[2] = 99;
	sir2[3] = 100;
	sir2[4] = 0;

	printf("\n%s\n", sir2);

	int x = 8, y = 7;
	interschimbareNumereIntregi(&x, &y);
	printf("\n\n%d %d\n", x, y);

	int nrElemente;
	int* vector;
	citireVectorTastatura(&vector, &nrElemente);

	printf("\n");
	for (int i = 0; i < nrElemente; i++) {
		printf("%d\t", vector[i]);
	}

	return 0;
}