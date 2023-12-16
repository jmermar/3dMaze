#include "ArbolBSP.h"

#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    Muro dato;
    struct Nodo * left, * right;
};

ArbolBSP arbol_bsp_crea(Muro* dato) {
    ArbolBSP arbol = malloc(sizeof(struct Nodo));
    arbol->dato = *dato;
    arbol->left = NULL;
    arbol->right = NULL;
    return arbol;
}

void arbol_bsp_destruye(ArbolBSP arbol) {
    if (!arbol) return;
    arbol_bsp_destruye(arbol->left);
    arbol_bsp_destruye(arbol->right);
    free(arbol);
}

void arbol_bsp_inserta_dato(ArbolBSP arbol, Muro* dato) {
    xy unit; //Vector unitario perpendicular a la recta de corte
    unit.x = arbol->dato.seg.e.y - arbol->dato.seg.s.y;
    unit.y = arbol->dato.seg.s.x - arbol->dato.seg.e.x;
    double l = mod(unit);
    unit.x /= l;
    unit.y /= l;

    xy p; //Coordenadas de un punto cualquiera de la recta de corte
    p.x = arbol->dato.seg.s.x;
    p.y = arbol->dato.seg.s.y;

    xy sr, er; //Coordenadas de los puntos del segmento dato relativos a p
    sr.x = dato->seg.s.x - p.x;
    sr.y = dato->seg.s.y - p.y;

    er.x = dato->seg.e.x - p.x;
    er.y = dato->seg.e.y - p.y;
    double y1 = dot(sr, unit);
    double y2 = dot(er, unit);

    if (y1 > 0.01) {
        if (y2 > 0.1) {
            if (arbol->right) {
                arbol_bsp_inserta_dato(arbol->right, dato);
            } else {
                arbol->right = arbol_bsp_crea(dato);
            }
        } else if (y2 < -0.1) {
            xy c = interseccion(&dato->seg, &arbol->dato.seg);

            Muro l1 = *dato;
            l1.seg.e = c;
            arbol_bsp_inserta_dato(arbol, &l1);

            Muro l2 = *dato;
            l2.seg.s = c;
            arbol_bsp_inserta_dato(arbol, &l2);
        } else {
            if (arbol->right) {
                arbol_bsp_inserta_dato(arbol->right, dato);
            } else {
                arbol->right = arbol_bsp_crea(dato);
            }
        }

    } else if (y1 < -0.1) {
        if (y2 < -0.1) {
            if (arbol->left) {
                arbol_bsp_inserta_dato(arbol->left, dato);
            } else {
                arbol->left = arbol_bsp_crea(dato);
            }
        } else if (y2 > 0.1) {
            xy c = interseccion(&dato->seg, &arbol->dato.seg);

            Muro l1 = *dato;

            l1.seg.e = c;
            arbol_bsp_inserta_dato(arbol, &l1);

            Muro l2 = *dato;
            l2.seg.s = c;

            arbol_bsp_inserta_dato(arbol, &l2);
        } else {
            if (arbol->left) {
                arbol_bsp_inserta_dato(arbol->left, dato);
            } else {
                arbol->left = arbol_bsp_crea(dato);
            }
        }
    } else {
        if (y2 > 0.1) {
            if (arbol->right) {
                arbol_bsp_inserta_dato(arbol->right, dato);
            } else {
                arbol->right = arbol_bsp_crea(dato);
            }
        } else {
            if (arbol->left) {
                arbol_bsp_inserta_dato(arbol->left, dato);
            } else {
                arbol->left = arbol_bsp_crea(dato);
            }
        }
    }
}

void arbol_bsp_dibuja(ArbolBSP arbol, xy cam_pos, double a, Imagen img) {
    if (!arbol || renderizado_buffer_lleno()) return;
    xy unit; //Vector unitario perpendicular a la recta de corte
    unit.x = arbol->dato.seg.e.y - arbol->dato.seg.s.y;
    unit.y = arbol->dato.seg.s.x - arbol->dato.seg.e.x;
    double l = mod(unit);
    unit.x /= l;
    unit.y /= l;

    double y = dot(resta(cam_pos, arbol->dato.seg.s), unit);
    if (y < 0) {
        arbol_bsp_dibuja(arbol->left, cam_pos, a, img);
        renderizado_dibuja_muro(&arbol->dato, cam_pos, a, img);
        arbol_bsp_dibuja(arbol->right, cam_pos, a, img);
    } else {
        arbol_bsp_dibuja(arbol->right, cam_pos, a, img);
        renderizado_dibuja_muro(&arbol->dato, cam_pos, a,  img);
        arbol_bsp_dibuja(arbol->left, cam_pos, a, img);
    }
}
