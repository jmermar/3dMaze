#ifndef _ARBOL_BSP_H_
#define _ARBOL_BSP_H_

#include "Renderizado.h"

/**
   \file ArbolBSP.h
   \brief  Arbol de partición binaria del espacio.
*/

/**
  \brief TDA ArbolBSP
*/
typedef struct Nodo * ArbolBSP;

/**
  \brief Crea un árbol con un dato.
  \param dato Puntero al dato a copiar como raíz del árbol.
  \return El arbol creado.
*/
ArbolBSP arbol_bsp_crea(Muro* dato);

/**
  \brief Libera la información de un árbol.
  \param arbol Arbol que se quiere destruir.
*/
void arbol_bsp_destruye(ArbolBSP arbol);

/**
  \brief Copia un dato dentro de un árbol.
  \param arbol Arbol donde se quiere copiar el dato.
  \param dato Puntero al dato a copiar.
*/
void arbol_bsp_inserta_dato(ArbolBSP arbol, Muro* dato);

/**
  \brief Dibuja los muros del árbol en perspectiva.
  \param arbol Árbol con los muros a dibujar.
  \param cam_pos Posición de la cámara desde la que dibujar.
  \param a Ángulo de la cámara con respecto al eje x.
  \param img Textura de los muros a dibujar.
*/
void arbol_bsp_dibuja(ArbolBSP arbol, xy cam_pos, double a, Imagen img);
#endif // _ARBOL_BSP_H_
