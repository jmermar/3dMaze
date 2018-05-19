#include "EditorLaberinto.h"

#include <stdio.h>
#include <stdlib.h>

#include "Pantalla.h"
#include "Ficheros.h"

#define X_LAB       216
#define TAM_CELDA   12

enum botones_acciones {
    accion_carga = 0, accion_guarda, accion_incrementa, accion_decrementa, num_acciones
};

char* botones_texto[] = {
    "Carga",
    "Guarda",
    "Incrementa tamano",
    "Decrementa tamano"
};

struct EditorLaberintoRep {
    int w, h;
    int* data;
    Imagen boton;
};

int get_indice(int x, int y, int w) {
    return y * w + x;
}

EditorLaberinto editor_laberinto_crea() {
    EditorLaberinto n = malloc(sizeof(struct EditorLaberintoRep));
    n->data = NULL;
    n->boton = Pantalla_ImagenLee("button.bmp", 1);
    return n;
}

void editor_laberinto_destruye(EditorLaberinto e) {
    if (e->data) free(e->data);
    free(e->boton);
    free(e);
}

void editor_laberinto_inicializa(EditorLaberinto e, int w, int h) {
    if (e->data) free(e->data);
    e->data = malloc(sizeof(int) * w * h);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (j == 0 || i == 0 || j == w - 1 || i == h - 1) {
                e->data[get_indice(j, i, w)] = 1;
            } else {
                e->data[get_indice(j, i, w)] = 0;
            }
        }
    }

    e->w = w;
    e->h = h;
}

void editor_laberinto_reescala(EditorLaberinto e, int w, int h) {
    int* nuevo = malloc(sizeof(int) * w * h);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int dato_a_copiar = 0;
            if (x < e->w && y < e->h) dato_a_copiar = e->data[get_indice(x, y, e->w)];
            nuevo[get_indice(x, y, w)] = dato_a_copiar;
        }
    }

    free(e->data);
    e->data = nuevo;
    e->w = w;
    e->h = h;
}

void editor_laberinto_carga(EditorLaberinto e, const char* src) {
    if (e->data) free(e->data);

    e->data = fichero_carga_nivel(src, &(e->w), &(e->h));
    if (e->data) {
        printf("Nivel cargado\n");
    } else {
        printf("No se pudo cargar el nivel, generando vacio\n");
        editor_laberinto_inicializa(e, 32, 32);
    }
}

void editor_laberinto_guarda(EditorLaberinto e, const char* src) {
    fichero_guarda_nivel(src, e->data, e->w, e->h);
    printf("Nivel guardado\n");
}

void editor_laberinto_click_izquierdo(EditorLaberinto e, double x, double y, int repetido) {
    if (x >= X_LAB) {
        int ix = (x - X_LAB) / TAM_CELDA;
        int iy = y / TAM_CELDA;
        if (ix < 0 || iy < 0 || ix >= e->w || iy >= e->h) return;
        e->data[get_indice(ix, iy, e->w)] = 1;
    }
    else if (x >= 0 && !repetido) {
        int nw = e->w, nh = e->h;
        int ind = y / Pantalla_ImagenAltura(e->boton);
        switch (ind) {
        case accion_carga:
            editor_laberinto_carga(e, "custom.txt");
            break;
        case accion_guarda:
            editor_laberinto_guarda(e, "custom.txt");
            break;
        case accion_incrementa:
            if (e->w < 32) nw++;
            if (e->h < 32) nh++;
            editor_laberinto_reescala(e, nw, nh);
            break;
        case accion_decrementa:
            if (e->w > 3) nw--;
            if (e->h > 3) nh--;
            editor_laberinto_reescala(e, nw, nh);
            break;
        }
    }
}

void editor_laberinto_click_derecho(EditorLaberinto e, double x, double y) {
    int ix = (x - X_LAB) / TAM_CELDA;
    int iy = y / TAM_CELDA;
    if (ix < 0 || iy < 0 || ix >= e->w || iy >= e->h) return;
    e->data[get_indice(ix, iy, e->w)] = 0;
}

void editor_laberinto_dibuja(EditorLaberinto e) {
    Pantalla_ColorTrazo(255, 255, 255, 255);
    for (int i = 0; i < num_acciones; i++) {
        double y = i * Pantalla_ImagenAltura(e->boton);
        Pantalla_DibujaImagen(e->boton, 0, y, Pantalla_ImagenAnchura(e->boton), Pantalla_ImagenAltura(e->boton));
        Pantalla_DibujaTexto(botones_texto[i], 8, y + 4);
    }
    for (int y = 0; y < e->h; y++) {
        for (int x = 0; x < e->w; x++) {
            double cx = X_LAB + x * TAM_CELDA;
            double cy = y * TAM_CELDA;

            if (e->data[get_indice(x, y, e->w)]) {
                    Pantalla_ColorTrazo(255, 255, 255, 255);
                    Pantalla_ColorRelleno(255, 255, 255, 255);
            } else {
                Pantalla_ColorTrazo(0, 0, 0, 255);
                Pantalla_ColorRelleno(0, 0, 0, 255);
            }

            Pantalla_DibujaRectangulo(cx, cy, TAM_CELDA, TAM_CELDA);
        }
    }
}
