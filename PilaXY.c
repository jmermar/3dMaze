#include "PilaXY.h"
#include <stdlib.h>
#include <assert.h>

#define MAX 4096

struct PilaXYRep {
    xy datos[MAX];
    int tope;
};

PilaXY pila_xy_crea() {
    PilaXY nuevo = malloc(sizeof(struct PilaXYRep));
    nuevo->tope = -1;
    return nuevo;
}

void pila_xy_destruye(PilaXY p) {
    free(p);
}

int pila_xy_es_vacia(PilaXY p) {
    return p->tope < 0;
}

xy pila_xy_recupera(PilaXY p) {
    return p->datos[p->tope];
}

void pila_xy_inserta(PilaXY p, xy valor) {
    p->datos[++(p->tope)] = valor;
    assert(p->tope < MAX);
}

void pila_xy_suprime(PilaXY p) {
    assert(p->tope >= 0);
    p->tope--;
}
