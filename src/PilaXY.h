#ifndef __PILA_XY_H__
#define __PILA_XY_H__

#include "Matematicas.h"

/**
   \file PilaXY.h
   \brief  Permite almacenar xy en una estructura de pila. Una pila es una estructura de datos donde sólo se puede acceder al último elemento y las inserciones y supresiones se realizan desde el final.
*/

/**
  \brief TDA PilaXY.
*/
typedef struct PilaXYRep * PilaXY;

/**
  \brief Crea un dato PilaXY.
  \return El dato creado.
*/
PilaXY pila_xy_crea();

/**
  \brief Libera una PilaXY.
  \param p La pila a ser liberada.
*/
void pila_xy_destruye(PilaXY p);

/**
  \brief Informa sobre si la pila está vacía o no. La pila estará vacía si no contiene ningún dato.
  \param p La pila que queremos comprobar si está vacía.
  \return 1 Si está vacía.
  \return 0 Si no está vacía.
*/
int pila_xy_es_vacia(PilaXY p);

/**
  \brief Devuelve la estructura xy almacenada en la cima de la pila.
  \param p La pila cuya cima queremos extraer.
  \return El dato almacenado en la cima de la pila
  \pre La pila no está vacía (contiene al menos un elemento)
*/
xy pila_xy_recupera(PilaXY p);

/**
  \brief Inserta un dato en la cima de la pila.
  \param p La pila donde queremos insertar el dato.
  \param valor El dato que queremos insertar.
*/
void pila_xy_inserta(PilaXY p, xy valor);

/**
  \brief Suprime el elemento de la cima de la pila.
  \param p La pila cuya cima queremos suprimir.
  \pre La pila no está vacía.
*/
void pila_xy_suprime(PilaXY p);
#endif // __PILA_XY_H__
