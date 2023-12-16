#include "Laberinto.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "ArbolBSP.h"
#include "PilaXY.h"
#include "Ficheros.h"

enum Direccion {
    arriba = 0, izquierda, abajo, derecha
};

int indice_real(int i) {
    return i * 2 + 1;
}

int* crea_laberinto(int s, int*w, int*h) {
    /**
     * El tamaño real del array es s*2 + 1 porque las posiciones con al sóloun índice par serán las 'conexiones' entre las casillas,
     * que son las posiciones com ambos índices impares. Las posiciones con ambos índices pares pueden ser ignoradas
     * Un 1 en una casilla significa que no está generada, mientra que un 1 en una conexión significa que entre las dos casillas que conecta hay un muro
     */
    int rs = s*2 + 1;

    *w = *h = rs;
    int* array = malloc(sizeof(int) * rs * rs);
    memset(array, 1, sizeof(int) * rs * rs); //Inicializa todas las casillas como no generadas y las conexiones a 1

    PilaXY pila = pila_xy_crea();
    xy casilla;
    casilla.x = 0; casilla.y = 0;
    pila_xy_inserta(pila, casilla);

    int dirs[4];

    while (!pila_xy_es_vacia(pila)) {
        casilla = pila_xy_recupera(pila);

        int x = indice_real(casilla.x);
        int y = indice_real(casilla.y);

        array[y * rs + x] = 0; //Marca la casilla como visitada

        int n = 0;

        if (casilla.y > 0 && array[(y-2) * rs + x]) dirs[n++] = arriba;
        if (casilla.y < s - 1 && array[(y+2) * rs + x]) dirs[n++] = abajo;
        if (casilla.x > 0 && array[y * rs + x - 2]) dirs[n++] = izquierda;
        if (casilla.x < s - 1 && array[y * rs + x + 2]) dirs[n++] = derecha;


        if (n <= 0) { //Si no hay casillas adyacentes libres
            pila_xy_suprime(pila);
            continue;
        }
        int d = dirs[rand() % n]; //Elige una dirección aleatoria
        if (d == arriba) {
            casilla.y--;
            array[(y-1) * rs + x] = 0;
        } else if (d == abajo) {
            casilla.y++;
            array[(y+1) * rs + x] = 0;
        } else if (d == izquierda) {
            casilla.x--;
            array[y * rs + x - 1] = 0;
        } else if (d == derecha) {
            casilla.x++;
            array[y * rs + x + 1] = 0;
        }
        pila_xy_inserta(pila, casilla);
    }

    int ey = 1 + 2 * (s / 2);
    array[ey * rs + rs - 1] = 0;
    return array;
}

struct LaberintoRep {
    ArbolBSP arbol;
    int w, h;
    int *lab;
    Imagen textura;
};

int colision(int lab[],int w, int h, int x, int y) {
    if (x < 0 || y < 0 || x >= w || y >= h) return 0;
    else return lab[y * h + x];
}

ArbolBSP crea_arbol(int lab[], int w, int h) {
    Muro wsplit;
    wsplit.visible = 0;
    wsplit.seg.s.y = wsplit.seg.e.y = h / 2;
    wsplit.seg.s.x = 0;
    wsplit.seg.e.x = w;

    ArbolBSP arbol = arbol_bsp_crea(&wsplit);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (colision(lab, w, h, j, i)) continue;
            Muro m;
            m.visible = 1;

            if (colision(lab, w, h, j, i - 1)) {
                m.seg.s.x = j;  m.seg.s.y = i;
                m.seg.e.x = j + 1;  m.seg.e.y = i;
                arbol_bsp_inserta_dato(arbol, &m);
            }

            if (colision(lab, w, h, j, i + 1)) {
                m.seg.s.x = j;  m.seg.s.y = i + 1;
                m.seg.e.x = j + 1;  m.seg.e.y = i + 1;
                arbol_bsp_inserta_dato(arbol, &m);
            }

            if (colision(lab, w, h, j - 1, i)) {
                m.seg.s.x = j;  m.seg.s.y = i;
                m.seg.e.x = j;  m.seg.e.y = i + 1;
                arbol_bsp_inserta_dato(arbol, &m);
            }

            if (colision(lab, w, h, j + 1, i)) {
                m.seg.s.x = j + 1;  m.seg.s.y = i;
                m.seg.e.x = j + 1;  m.seg.e.y = i + 1;
                arbol_bsp_inserta_dato(arbol, &m);
            }
        }
    }

    return arbol;
}

Laberinto laberinto_crea() {
    Laberinto nuevo = malloc(sizeof(struct LaberintoRep));
    nuevo->lab = crea_laberinto(8, &nuevo->w, &nuevo->h);

    nuevo->arbol = crea_arbol(nuevo->lab, nuevo->w, nuevo->h);
    nuevo->textura = Pantalla_ImagenLee("wall.bmp", 0);

    return nuevo;
}

Laberinto laberinto_carga(const char* src) {
    Laberinto nuevo = malloc(sizeof(struct LaberintoRep));
    nuevo->lab = fichero_carga_nivel(src, &nuevo->w, &nuevo->h);
    if (!nuevo->lab) {
        free(nuevo);
        return NULL;
    }

    nuevo->arbol = crea_arbol(nuevo->lab, nuevo->w, nuevo->h);
    nuevo->textura = Pantalla_ImagenLee("wall.bmp", 0);

    return nuevo;
}

void laberinto_destruye(Laberinto l) {
    free(l->lab);
    free(l->textura);
    free(l);
}

void laberinto_dibuja(Laberinto l, xy cam_pos, double a) {
    arbol_bsp_dibuja(l->arbol, cam_pos, a, l->textura);
}

int laberinto_comprueba_colision(Laberinto l, int x, int y) {
    return colision(l->lab, l->w, l->h, x, y);
}

xy laberinto_get_size(Laberinto l) {
    xy ret;
    ret.x = l->w;
    ret.y = l->h;
    return ret;
}
