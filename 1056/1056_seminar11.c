#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct Haina Haina;
typedef struct Heap Heap;

struct Haina
{
	int prioritate;
	char* denumire;
	char* marime;
};

struct Heap
{
	Haina* haine;
	int dim;
	int maxdim;
};

Haina initializareHaina(int prioritate, char* denumire, char* marime)
{
	Haina h;
	h.prioritate = prioritate;
	h.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(h.denumire, denumire);
	h.marime = (char*)malloc(strlen(marime) + 1);
	strcpy(h.marime, marime);

	return h;
}

void afisareHaina(Haina h)
{
	printf("Haina cu prioritatea %i are denumirea %s si marimea %s\n", h.prioritate, h.denumire, h.marime);
}

void afisareHeap(Heap h)
{
	for (int i = 0; i < h.dim; i++)
	{
		afisareHaina(h.haine[i]);
	}
}

void afisareHeapMax(Heap h)
{
	for (int i = 0; i < h.maxdim; i++)
	{
		afisareHaina(h.haine[i]);
	}
}

void filtrareHeap(Heap h, int index) {
	if (h.dim) {
		int index_dreapta;
		int index_stanga;
		index_stanga = 2 * index + 1;
		index_dreapta = 2 * index + 2;
		int index_max = index;
		if (h.dim > index_stanga && h.haine[index_max].prioritate < h.haine[index_stanga].prioritate) {
			index_max = index_stanga;
		}
		if (h.dim > index_dreapta && h.haine[index_max].prioritate < h.haine[index_dreapta].prioritate) {
			index_max = index_dreapta;

		}
		if (index_max != index) {
			Haina aux;
			aux = h.haine[index];
			h.haine[index] = h.haine[index_max];
			h.haine[index_max] = aux;
			if (index_max < h.dim / 2 - 1) {
				filtrareHeap(h, index_max);
			}
		}
	}
}

void extragere(Heap* h, Haina* haina) {
	(*haina) = initializareHaina(h->haine[0].prioritate, h->haine[0].denumire, h->haine[0].marime);
	Haina aux;
	aux = h->haine[0];
	h->haine[0] = h->haine[h->dim - 1];
	h->haine[h->dim - 1] = aux;
	h->dim -= 1;
	filtrareHeap((*h), 0);
}

void main()
{
	Heap h;
	h.dim = 6;
	h.maxdim = 6;

	h.haine = (Haina*)malloc(sizeof(Haina) * h.dim);
	h.haine[0].prioritate = 3;
	h.haine[0].denumire = "bluza";
	h.haine[0].marime = "M";
	h.haine[1] = initializareHaina(6, "pantaloni", "L");
	h.haine[2] = initializareHaina(2, "camasa", "S");
	h.haine[3] = initializareHaina(1, "blugi", "XL");
	h.haine[4] = initializareHaina(5, "tricou", "M");
	h.haine[5] = initializareHaina(4, "fusta", "S");

	for (int i = (h.dim / 2) - 1; i >= 0; i--) {
		filtrareHeap(h, i);

	}
	afisareHeap(h);

	Haina haina;
	printf("\n");
	while (h.dim != 0) {
		extragere(&h, &haina);
		afisareHaina(haina);
		free(haina.denumire);
		free(haina.marime);
	}

	printf("\n");
	afisareHeapMax(h);
}