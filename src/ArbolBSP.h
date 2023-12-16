#ifndef _ARBOL_BSP_H_
#define _ARBOL_BSP_H_

#include "Renderizado.h"

/**
   \file ArbolBSP.h
   \brief  Arbol de partici�n binaria del espacio.
*/

/**
  \brief TDA ArbolBSP
*/
typedef struct Nodo * ArbolBSP;

/**
  \brief Crea un �rbol con un dato.
  \param dato Puntero al dato a copiar como ra�z del �rbol.
  \return El arbol creado.
*/
ArbolBSP arbol_bsp_crea(Muro* dato);

/**
  \brief Libera la informaci�n de un �rbol.
  \param arbol Arbol que se quiere destruir.
*/
void arbol_bsp_destruye(ArbolBSP arbol);

/**
  \brief Copia un dato dentro de un �rbol.
  \param arbol Arbol donde se quiere copiar el dato.
  \param dato Puntero al dato a copiar.
*/
void arbol_bsp_inserta_dato(ArbolBSP arbol, Muro* dato);

/**
  \brief Dibuja los muros del �rbol en perspectiva.
  \param arbol �rbol con los muros a dibujar.
  \param cam_pos Posici�n de la c�mara desde la que dibujar.
  \param a �ngulo de la c�mara con respecto al eje x.
  \param img Textura de los muros a dibujar.
*/
void arbol_bsp_dibuja(ArbolBSP arbol, xy cam_pos, double a, Imagen img);
#endif // _ARBOL_BSP_H_
