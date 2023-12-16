#ifndef _LABERINTO_H_
#define _LABERINTO_H_
#include "Matematicas.h"

/**
   \file Laberinto.h
   \brief TDA Laberinto y su interfaz.
*/


/**
   \brief TDA Laberinto.
*/
typedef struct LaberintoRep * Laberinto;

/**
   \brief Crea un laberinto.
   \return El laberinto.
*/
Laberinto laberinto_crea();
/**
   \brief Crea un laberinto cargándolo desde un fichero.
   \param Ruta del fichero.
   \return El laberinto guardado en el fichero o uno aleatorio si no pudo cargarlo.
*/
Laberinto laberinto_carga(const char* src);
/**
   \brief Destruye un laberinto.
   \param l El laberinto a destruir.
*/
void laberinto_destruye(Laberinto l);
/**
   \brief Comprueba si un en un punto hay una pared o no.
   \param l El laberinto.
   \param x La coordenada x del punto.
   \param y La coordenada y del punto.
   \return 1 Si ese punto está dentro de una pared.
   \return 0 Si ese punto no está dentro de una pared.
*/
int laberinto_comprueba_colision(Laberinto l, int x, int y);
/**
   \brief Devuelve el la anchura y la altura del laberinto.
   \param l El laberinto cuyas dimensiones se quieren conocer.
   \return El tamaño del laberinto.
*/
xy laberinto_get_size(Laberinto l);
/**
   \brief Dibuja el laberinto desde la perspectiva de una cámara.
   \param l El laberinto a dibujar.
   \param cam_pos Posición de la cámara.
   \param a Ángulo de la cámara.
*/
void laberinto_dibuja(Laberinto l, xy cam_pos, double a);
#endif // _LABERINTO_H_
