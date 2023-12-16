#include "Ficheros.h"

#include <stdlib.h>
#include <stdio.h>

int* fichero_carga_nivel(const char* fichero, int* w, int* h) {
	FILE* f = fopen(fichero, "r");

	int width, height;
	if (!f || fscanf(f, "%d %d\n", &width, &height) != 2 || width < 0 || height < 0 || width > 32 || height > 32) {
		printf("No existe el fichero '%s' o su contenido es invalido\n", fichero);

		if (f) fclose(f);
		return NULL;
	}

	int* arr = malloc(sizeof(int) * width * height);
	int* actual = arr;

	while (fscanf(f, "%d ", actual) == 1 && actual - arr < width * height) actual++;

	fclose(f);

	*w = width;
	*h = height;
	return arr;
}

void fichero_guarda_nivel(const char* fichero, int* nivel, int w, int h) {
	FILE* f = fopen(fichero, "w");
	fprintf(f, "%d %d\n", w, h);

	for (int i = 0; i < w * h; i++) {
		fprintf(f, "%d ", nivel[i]);
	}
	fclose(f);
}
