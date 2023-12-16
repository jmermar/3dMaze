#ifndef __FICHEROS_H__
#define __FICHEROS_H__

/**
   \file Ficheros.h
   \brief Las funciones para cargar y guardar niveles de ficheros.
*/

/**
   \brief Lee el fichero pasado como parámetro y devuelve un array con su contenido.
   \param path La ruta del fichero a cargar.
   \param w Puntero a la variable donde almacenar el ancho del nivel.
   \param h Puntero a la variable donde almacenar el alto del nivel.
   \return Puntero al primer elemento del array que contiene la información del nivel.
*/
int* fichero_carga_nivel(const char* path, int* w, int* h);
/**
   \brief Escribe en el fichero pasado como parámetro el array pasado cómo parámetro.
   \param path La ruta del fichero a guardar.
   \param nivel Puntero al primer elemento del array con la información del nivel a guardar.
   \param w El ancho del nivel.
   \param g El alto del nivel.
*/
void fichero_guarda_nivel(const char* path, int* nivel, int w, int h);

#endif // __FICHEROS_H__
