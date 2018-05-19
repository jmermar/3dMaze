#ifndef _MATEMATICAS_H_
#define _MATEMATICAS_H_
#include <math.h>

#define PI 3.14159265359

/**
   \file Matematicas.h
   \brief Funciones comunes con números, puntos y rectas.
*/
typedef struct {
    double x, y;
} xy;

typedef struct {
    xy s, e;
} Segmento;
/**
   \brief Devuelve el mayor de dos enteros.
   \param a Primer entero.
   \param b Segundo entero.
   \return a Si a es mayor que b.
   \return b Si no es cierto que a sea mayor que b.
*/
int imax(int a, int b);
/**
   \brief Devuelve el menor de dos enteros.
   \param a Primer entero.
   \param b Segundo entero.
   \return a Si a es menor que b.
   \return b Si no es cierto que a sea menor que b.
*/
int imin(int a, int b);
/**
   \brief Devuelve el valor absoluto de un entero.
   \param a El entero.
   \return |a| Esto es, a sin signo.
*/
int iabs(int a);
/**
   \brief Devuelve el cuadrado de un real.
   \param a El real.
   \return a al cuadrado.
*/
double square(double a);
/**
   \brief Devuelve el módulo(longitud) de un vector.
   \param vec Coordenadas del vector.
   \return Módulo de vec.
*/
double mod(xy vec);
/**
   \brief Devuelve el producto escalar de dos vectores.
   \param a Coordenadas del primer vector.
   \param b Coordenadas del segundo vector.
   \return Producto escalar de ambos vectores.
*/
double dot(xy a, xy b);
/**
   \brief Devuelve la suma de dos vectores.
   \param a Coordenadas del primer vector.
   \param b Coordenadas del segundo vector.
   \return Suma de ambos vectores.
*/
xy suma(xy a, xy b);
/**
   \brief Devuelve la resta de dos vectores.
   \param a Coordenadas del primer vector.
   \param b Coordenadas del segundo vector.
   \return Resta de ambos vectores.
*/
xy resta(xy a, xy b);
/**
   \brief .
*/
xy producto(xy a, double s);
/**
   \brief Devuelve la intersección de dos rectas.
   \param a Dirección a un segmento contenido en la primera recta.
   \param b Dirección a un segmento contenida en la segunda recta.
   \pre Las dos rectas se cortan en un único punto.
   \return Coordenadas de la intersección de ambas rectas.
*/
xy interseccion(Segmento* a, Segmento* b);

#endif // _MATEMATICAS_H_
