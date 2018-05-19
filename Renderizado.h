#ifndef _RENDERIZADO_H_
#define _RENDERIZADO_H_

#include "Pantalla.h"
#include "Matematicas.h"

/**
   \file Renderizado.h
   \brief  Este fichero incluye las funciones para dibujar en tres dimensiones muros, sin embargo, no garantiza que se dibujen en el orden correcto.
*/

#define PANTALLA_W 640
#define PANTALLA_H 480

/**
   \brief  Un muro es una pared definida por dos puntos que son las coordenadas de sus extremos y un valor booleano que indica si se ignorará o nó al ser dibujado.
*/
typedef struct {
    Segmento seg;
    int visible;
} Muro;

/**
  \brief Limpia la pantalla.
*/
void renderizado_limpia_pantalla();

/**
  \brief Indica si se han dibujado todas las lineas verticales de la pantalla.
  \return 1 Si se han dibujado todas las lineas verticales de la pantalla.
  \return 0 Si aún quedan lineas verticales por rellenar.
*/
int renderizado_buffer_lleno();

/**
  \brief Dibuja un muro en perspectiva.
  \param muro El muro a dibujar.
  \param cam_pos La posición de la cámara desde la que dibujar
  \param angle Ángulo de la cámara con respecto al eje horizontal.
  \param textura Imagen que aplicar al muro.
*/
void renderizado_dibuja_muro(Muro *muro, xy cam_pos, double angle, Imagen textura);
#endif // _RENDERIZADO_H_
