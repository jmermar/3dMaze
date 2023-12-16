#include "Estados.h"

#include <stdio.h>
#include <assert.h>

#include "Pantalla.h"
#include "Jugador.h"
#include "Laberinto.h"
#include "Renderizado.h"
#include "EditorLaberinto.h"

int juego_bucle(Jugador j, Laberinto l) {
	int siguiente = -1;

	xy tam_lab = laberinto_get_size(l);

	while (Pantalla_Activa() && siguiente < 0) {
		if (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)) {
			siguiente = estado_menu;
			break;
		}

		jugador_actualiza(j, l);

		xy jpos = jugador_get_pos(j);
		if (jpos.x < 0 || jpos.y < 0 || jpos.x > tam_lab.x || jpos.y > tam_lab.y) {
			siguiente = estado_superado;
		}

		renderizado_limpia_pantalla();
		laberinto_dibuja(l, jpos, jugador_get_angle(j));
		Pantalla_Actualiza();

		Pantalla_Espera(10);
	}

	return siguiente;
}

int menu_run() {
	int siguiente = -1;

	Imagen fondo = Pantalla_ImagenLee("back.bmp", 0);
	Imagen cursor = Pantalla_ImagenLee("cursor.bmp", 1);

	int indice = 0;
	int acciones[3] = {
		estado_juego,
		estado_carga,
		estado_crea
	};

	int arriba_pulsado = 0;
	int abajo_pulsado = 0;

	double oscilacion = 0;

	while (Pantalla_Activa() && siguiente == -1) {
		if (Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE)) {
			siguiente = acciones[indice];
		}

		//Mueve el cursor si resulta necesario
		if (Pantalla_TeclaPulsada(SDL_SCANCODE_UP)) {
			if (!arriba_pulsado) {
				arriba_pulsado = 1;
				indice = (3 + indice - 1) % 3;
			}
		}
		else {
			arriba_pulsado = 0;
		}
		if (Pantalla_TeclaPulsada(SDL_SCANCODE_DOWN)) {
			if (!abajo_pulsado) {
				abajo_pulsado = 1;
				indice = (indice + 1) % 3;
			}
		}
		else {
			abajo_pulsado = 0;
		}

		oscilacion += 0.05;
		if (oscilacion >= PI * 2) oscilacion -= PI * 2;


		Pantalla_DibujaImagen(fondo, 0, 0, 640, 480);
		Pantalla_ColorTrazo(255, 255, 255, 255);
		Pantalla_DibujaTexto("Jugar nivel aleatorio", 100, 320);
		Pantalla_DibujaTexto("Cargar nivel", 100, 340);
		Pantalla_DibujaTexto("Crear nivel", 100, 360);

		Pantalla_DibujaImagen(cursor, 80 + cos(oscilacion) * 3, 320 + indice * 20, 16, 16);

		Pantalla_Espera(10);
		Pantalla_Actualiza();
	}

	Pantalla_ImagenLibera(cursor);
	Pantalla_ImagenLibera(fondo);
	return siguiente;
}

int juego_run() {
	Jugador jugador = jugador_crea(1.5, 1.5, 0);
	Laberinto l = laberinto_crea();

	int siguiente = juego_bucle(jugador, l);

	jugador_destruye(jugador);
	laberinto_destruye(l);

	return siguiente;
}

int juego_carga_run() {
	Jugador jugador = jugador_crea(1.5, 1.5, 0);
	Laberinto l = laberinto_carga("custom.txt");

	if (!l) {
		printf("No se pudo cargar el laberinto personalizado, se creara uno proceduralmente\n");
		l = laberinto_crea();
	}

	int siguiente = juego_bucle(jugador, l);

	jugador_destruye(jugador);
	laberinto_destruye(l);

	return siguiente;
}

int juego_crea() {
	int siguiente = -1;

	Imagen fondo = Pantalla_ImagenLee("back.bmp", 0);
	EditorLaberinto e = editor_laberinto_crea();
	editor_laberinto_carga(e, "custom.txt");

	double mx, my;
	int click_repetido = 0;

	while (Pantalla_Activa() && siguiente == -1) {
		Pantalla_RatonCoordenadas(&mx, &my);
		if (Pantalla_RatonBotonPulsado(SDL_BUTTON_LEFT)) {
			editor_laberinto_click_izquierdo(e, mx, my, click_repetido);
			click_repetido = 1;
		}
		else {
			click_repetido = 0;
		}
		if (Pantalla_RatonBotonPulsado(SDL_BUTTON_RIGHT)) {
			editor_laberinto_click_derecho(e, mx, my);
		}

		if (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)) {
			siguiente = estado_menu;
		}

		Pantalla_DibujaImagen(fondo, 0, 0, 640, 480);

		editor_laberinto_dibuja(e);

		Pantalla_ColorTrazo(255, 255, 255, 255);

		Pantalla_Actualiza();
		Pantalla_Espera(10);
	}

	editor_laberinto_destruye(e);
	Pantalla_ImagenLibera(fondo);
	return siguiente;
}

int juego_superado() {
	int siguiente = -1;

	Imagen fondo = Pantalla_ImagenLee("back.bmp", 0);

	while (Pantalla_Activa() && siguiente == -1) {
		if (Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE)) {
			siguiente = estado_menu;
			Pantalla_Espera(500);
		}

		Pantalla_DibujaImagen(fondo, 0, 0, 640, 480);
		Pantalla_ColorTrazo(255, 255, 255, 255);

		Pantalla_DibujaTexto("Nivel superado!", 100, 320);
		Pantalla_DibujaTexto("Pulsa espacio para volver al menu", 100, 340);

		Pantalla_Espera(10);
		Pantalla_Actualiza();
	}

	Pantalla_ImagenLibera(fondo);
	return siguiente;
}

int ejecuta_estado(int estado) {
	static int (*s[5]) () = {
		menu_run, juego_run, juego_carga_run, juego_crea, juego_superado
	};
	return s[estado]();
}
