#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include "Matematicas.h"
#include "Laberinto.h"

/**
   \file Jugador.h
   \brief TDA Jugador y su interfaz.
*/


/**
   \brief TDA Jugador.
*/
typedef struct JugadorRep * Jugador;
/**
   \brief Crea un jugador.
   \param x Coordenada x de inicio.
   \param y Coordenada y de inicio.
   \param angle Ángulo inicial.
   \return puntero al jugador
*/
Jugador jugador_crea(double x, double y, double angle);
/**
   \brief Destruye un jugador.
   \param j El jugador a destruir.
*/
void jugador_destruye(Jugador j);
/**
   \brief La función actualiza debe ser llamada en cada iteración del bucle principal, actualiza el estado del jugador como por ejemplo moviéndolo de posición según las teclas pulsadas.
   \param j El jugador a actualizar.
   \param l El laberinto donde se encuentra el jugador.
*/
void jugador_actualiza(Jugador j, Laberinto l);
/**
   \brief Devuelve la posición del jugador.
   \param j El jugador cuya posición se quiere conocer.
   \return Estructura xy con la x y la y del jugador.
*/
xy jugador_get_pos(Jugador j);
/**
   \brief Devuelve el ángulo con el que el jugador está rotado con respecto al eje x de coordenadas.
   \param j EL jugador cuyo ángulo se quiere conocer.
   \return El ángulo del jugador pasado como parámetro.
*/
double jugador_get_angle(Jugador j);

#endif // _JUGADOR_H_
