#include "Jugador.h"

#include <stdlib.h>
#include <math.h>

#include "Pantalla.h"

#define SPEED 0.018

struct JugadorRep {
    double x, y, angle;
};

Jugador jugador_crea(double x, double y, double angle) {
    Jugador j = malloc(sizeof(struct JugadorRep));
    j->x = x;
    j->y = y;
    j->angle = angle;
    return j;
}

void jugador_destruye(Jugador j) {
    free(j);
}

int colisionando(Jugador j, Laberinto l) {
    return  laberinto_comprueba_colision(l, j->x - 0.2, j->y - 0.2) ||
            laberinto_comprueba_colision(l, j->x + 0.2, j->y - 0.2) ||
            laberinto_comprueba_colision(l, j->x - 0.2, j->y + 0.2) ||
            laberinto_comprueba_colision(l, j->x + 0.2, j->y + 0.2);
}

void jugador_actualiza(Jugador j, Laberinto l) {
    double x_up, y_up;
    x_up = cos(j->angle);
    y_up = sin(j->angle);

    if (Pantalla_TeclaPulsada(SDL_SCANCODE_UP)) {
        j->x += x_up * SPEED;
        if (colisionando(j, l)) j->x -= x_up * SPEED;
        j->y += y_up * SPEED;
        if (colisionando(j, l)) j->y -= y_up * SPEED;
    }

    if (Pantalla_TeclaPulsada(SDL_SCANCODE_DOWN)) {
        j->x -= x_up * SPEED;
        if (colisionando(j, l)) j->x += x_up * SPEED;
        j->y -= y_up * SPEED;
        if (colisionando(j, l)) j->y += y_up * SPEED;
    }

    if (Pantalla_TeclaPulsada(SDL_SCANCODE_LEFT)) j->angle += PI/(6*16);
    if (Pantalla_TeclaPulsada(SDL_SCANCODE_RIGHT)) j->angle -= PI/(6*16);
}

xy jugador_get_pos(Jugador j) {
    xy ret = {j->x, j->y};
    return ret;
}

double jugador_get_angle(Jugador j) {
    return j->angle;
}
