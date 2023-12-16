#ifndef __EDITOR_LABERINTO_H__
#define __EDITOR_LABERINTO_H__

/**
   \file EditorLaberinto.h
   \brief Este fichero incluye la interfaz para usar el TDA editor laberinto, con el que el usuario puede editar sus propios laberintos.
*/


/**
   \brief TDA EditorLaberinto.
*/
typedef struct EditorLaberintoRep * EditorLaberinto;

/**
   \brief Crea un EditorLaberinto.
   \return El EdiorLaberinto creado.
*/
EditorLaberinto editor_laberinto_crea();

/**
   \brief Destruye un EditorLaberinto, el laberinto debe ser inicializado antes de utilizarse.
   \return El EditorLaberinto a destruir.
*/
void editor_laberinto_destruye(EditorLaberinto e);

/**
   \brief Inicializa el laberinto al tamaño indicado, dejándolo todo vacío con excepción de los bordes.
   \param e El EditorLaberinto a inicializar.
   \param w La nueva anchura del laberinto.
   \param h La nueva altura del laberinto.
*/
void editor_laberinto_inicializa(EditorLaberinto e, int w, int h);

/**
   \brief Inicializa el laberinto o bien cargándolo desde el fichero indicado o inicianizándolo con un tamaño de 32x32 si el fichero no existe o no es válido.
   \param e El EditorLaberinto a cargar.
   \param src La dirección del fichero desde el que se intentará cargar el laberinto.
*/
void editor_laberinto_carga(EditorLaberinto e, const char* src);

/**
   \brief Guarda el laberinto en un fichero.
   \param e El EditorLaberinto a guardar.
   \param src El nombre del fichero donde se guardará.
*/
void editor_laberinto_guarda(EditorLaberinto e, const char* src);

/**
   \brief Reescala un laberinto inicializado.
   \param e EditorLaberinto a ser reescalado.
   \param w La nueva anchura del laberinto.
   \param h La nueva altura del laberinto.
   \pre Se debe pasar un laberinto que haya sido inicializado por medio de editor_laberinto_inicializa o editor_laberinto_carga.
*/
void editor_laberinto_reescala(EditorLaberinto e, int w, int h);

/**
   \brief Hay que llamar a esta función cuando el usuario haga click izquierdo en la pantalla.
   \param e El EditorLaberinto que esté siendo usado.
   \param x La coordenada x del ratón.
   \param y La coordenada y del ratón.
   \param repetido Debe ser 0 si se acaba de pulsar el ratón o 1 en caso contrario.
   \pre Se debe pasar un laberinto que haya sido inicializado por medio de editor_laberinto_inicializa o editor_laberinto_carga.
*/
void editor_laberinto_click_izquierdo(EditorLaberinto e, double x, double y, int repetido);

/**
   \brief Hay que llamar a esta función cuando el usuario haga click derecho en la pantalla.
   \param e El EditorLaberinto que esté siendo usado.
   \param x La coordenada x del ratón.
   \param y La coordenada y del ratón.
   \pre Se debe pasar un laberinto que haya sido inicializado por medio de editor_laberinto_inicializa o editor_laberinto_carga.
*/
void editor_laberinto_click_derecho(EditorLaberinto e, double x, double y);

/**
   \brief Dibuja el laberinto en pantalla.
   \param e El laberinto a dibujar.
   \pre Se debe pasar un laberinto que haya sido inicializado por medio de editor_laberinto_inicializa o editor_laberinto_carga.
*/
void editor_laberinto_dibuja(EditorLaberinto e);
#endif // __EDITOR_LABERINTO_H__
