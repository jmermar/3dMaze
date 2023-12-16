#include "Estados.h"
#include "Pantalla.h"
#include "Renderizado.h"

int main(int argc, char** argv) {
    Pantalla_Crea("3D Maze", PANTALLA_W, PANTALLA_H);

    int estado = estado_menu;

    while(estado != -1) {
        estado = ejecuta_estado(estado);
    }

    Pantalla_Libera();
    return 0;
}
