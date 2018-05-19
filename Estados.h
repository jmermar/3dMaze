#ifndef __ESTADOS_H__
#define __ESTADOS_H__

/**
   \file Estados.h
   \brief Este fichero abstrae al usuario de la lógica de los diferentes estados de cada juego.
*/

enum Estados {
    estado_menu = 0, estado_juego = 1, estado_carga = 2, estado_crea = 3, estado_superado = 4
};

/**
   \brief Ejecuta el estado que se pase como parámetro.
   \param estado El estado a ejecutar.
   \return -1 si se debe cerrar la aplicación.
   \return El siguiente estado a ejecutar.
*/
int ejecuta_estado(int estado);

#endif // __ESTADOS_H__
