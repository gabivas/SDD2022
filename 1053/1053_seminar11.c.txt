#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Echipa Echipa;
typedef struct Heap Heap;

struct Echipa {
	int prioritate;
	char* nume;
};

struct Heap {
	Echipa* echipe;
	int dim;
	int maxDim;
};

Echipa initEchipa(int id, char* nume) {
	Echipa echipa;
	echipa.prioritate = id;
	echipa.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(echipa.nume, nume);
	return echipa;
}

void afisareEchipe(Heap heap) {
	for (int i = 0; i < heap.dim; i++) {
		printf("%d. Echipa %s\n", heap.echipe[i].prioritate, heap.echipe[i].nume);
	}
}

void filtrare(Heap heap, int index)
{
	if (heap.dim)
	{
		int is = 2 * index + 1;
		int id = 2 * index + 2;
		int index_max = index;
		if (is < heap.dim && heap.echipe[index_max].prioritate < heap.echipe[is].prioritate)
			index_max = is;
		if (id < heap.dim && heap.echipe[index_max].prioritate < heap.echipe[id].prioritate)
			index_max = id;
		if (index_max != index)
		{
			Echipa aux = heap.echipe[index];
			heap.echipe[index] = heap.echipe[index_max];
			heap.echipe[index_max] = aux;
		}
		if (index_max < heap.dim / 2 - 1)
			filtrare(heap, index_max);
	}
}

Echipa extragere(Heap* heap)
{
	Echipa e;
	e.prioritate = heap->echipe[0].prioritate;
	e.nume = (char*)malloc(strlen(heap->echipe[0].nume) + 1);
	strcpy(e.nume, heap->echipe[0].nume);

	Echipa aux = heap->echipe[0];
	heap->echipe[0] = heap->echipe[heap->dim - 1];
	heap->echipe[heap->dim - 1] = aux;

	heap->dim--;
	filtrare(*heap, 0);
	return e;
}

void afisareEchipeMax(Heap heap) {
	for (int i = 0; i < heap.maxDim; i++) {
		printf("%d. Echipa %s\n", heap.echipe[i].prioritate, heap.echipe[i].nume);
	}
}

void main() {
	Heap heap;
	heap.dim = 6;
	heap.echipe = (Echipa*)malloc(sizeof(Echipa) * heap.dim);
	heap.maxDim = 6;
	heap.echipe[0].prioritate = 1;
	heap.echipe[0].nume = "Steaua";
	heap.echipe[1].prioritate = 3;
	heap.echipe[1].nume = "Otelul Galati";
	heap.echipe[2].prioritate = 6;
	heap.echipe[2].nume = "Pisicile Salbatice";
	heap.echipe[3].prioritate = 5;
	heap.echipe[3].nume = "Power Rangers";
	heap.echipe[4].prioritate = 2;
	heap.echipe[4].nume = "Rapid";
	heap.echipe[5].prioritate = 4;
	heap.echipe[5].nume = "Dinamo";
	afisareEchipe(heap);

	for (int i = heap.dim / 2 - 1; i >= 0; i--)
	{
		filtrare(heap, i);
	}
	printf("\n\n");
	afisareEchipe(heap);

	while (heap.dim)
	{
		Echipa e = extragere(&heap);
		free(e.nume);
	}
	printf("\n\n");
	afisareEchipeMax(heap);
}