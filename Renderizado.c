#include "Renderizado.h"

char lineas_dibujadas[PANTALLA_W];
int lineas_restantes;

xy a_coordenadas_pantalla(xy c) {
    xy ret;
    ret.x = (PANTALLA_W / 2) + (PANTALLA_H / 2) * c.x;
    ret.y = (PANTALLA_H / 2) * (1 - c.y);
    return ret;
}

xy proyectar(xy punto, double h) {
    xy ret;
    ret.x = punto.x / punto.y;
    ret.y = h / punto.y;

    return ret;
}

void renderizado_limpia_pantalla() {
    for (int i = 0; i < PANTALLA_W; i++) lineas_dibujadas[i] = 0;
    lineas_restantes = PANTALLA_W;

    Pantalla_DibujaRellenoFondo(0, 0, 0, 0);
}

int renderizado_buffer_lleno() {
    return lineas_restantes <= 0;
}

void renderizado_dibuja_muro(Muro* muro, xy cam_pos, double a, Imagen img) {
    if (!muro->visible) return;

    //Los vectores unitarios que representan la direccion de la camara
    xy cam_up, cam_left;
    cam_up.x = cos(a);
    cam_up.y = sin(a);

    cam_left.x = cam_up.y;
    cam_left.y = -cam_up.x;

    Segmento rel_seg; //Segmento del muro pero relativo a la cámara
    rel_seg.s.x = dot(resta(muro->seg.s, cam_pos), cam_left);
    rel_seg.s.y = dot(resta(muro->seg.s, cam_pos), cam_up);

    rel_seg.e.x = dot(resta(muro->seg.e, cam_pos), cam_left);
    rel_seg.e.y = dot(resta(muro->seg.e, cam_pos), cam_up);

    if (rel_seg.s.y < 0.1 && rel_seg.e.y < 0.1) return;//Si el segmento están detrás de la cámara no hacer nada

    //Clipear el segmento con el eje x si resulta necesario
    xy clip, dir;
    dir = resta(rel_seg.s, rel_seg.e);
    clip.y = 0.1;
    clip.x = rel_seg.s.x + (dir.x / dir.y) * (0.1 - rel_seg.s.y);

    double txt_s = 0, txt_e = 1; //Coordenadas de la textura normalizadas
    double wall_length = mod(resta(rel_seg.s, rel_seg.e));
    if (rel_seg.s.y < 0.1) {
        txt_s = mod(resta(clip, rel_seg.s)) / wall_length;
        rel_seg.s = clip;
    }
    else if (rel_seg.e.y < 0.1) {
        txt_e = 1 - (mod(resta(clip, rel_seg.e)) / wall_length);
        rel_seg.e = clip;
    }

    xy c00, c10; //Esquinas de la pared proyectadas
    c00 = proyectar(rel_seg.s, 0.5);
    c10 = proyectar(rel_seg.e, 0.5);

    xy s00, s10; //Esquinas de la pared en coordenadas de pantalla
    s00 = a_coordenadas_pantalla(c00);
    s10 = a_coordenadas_pantalla(c10);

    int from, to, y_from, y_to;
    double z0, z1;
    double u0, u1;
    if (s00.x < s10.x) {
        from = s00.x;
        to = s10.x;
        y_from = s00.y;
        y_to = s10.y;
        z0 = rel_seg.s.y;
        z1 = rel_seg.e.y;
        u0 = txt_s;
        u1 = txt_e;
    } else {
        from = s10.x;
        to = s00.x;
        y_from = s10.y;
        y_to = s00.y;
        z0 = rel_seg.e.y;
        z1 = rel_seg.s.y;
        u0 = txt_e;
        u1 = txt_s;
    }

    double dx = to - from;
    double delta = (y_to - y_from) / dx;

    Pantalla_ColorTrazo(25, 100, 100, 255);
    for (int i = imax(0, from); i < imin(PANTALLA_W - 1, to); i++ ) {
        if (lineas_dibujadas[i]) continue;
        lineas_restantes--;
        lineas_dibujadas[i] = 1;

        int top = y_from + (i - from) * delta;
        int bottom = PANTALLA_H - top;

        double ni = (float) (i - from) / dx;

        //Algoritmo sacado de la página "Texture Mapping" de la Wikipedia
        double n_tex =  ((1 - ni) * (u0 / z0) + ni*(u1/z1)) /
                        ((1- ni) * (1/z0) + ni * (1/z1));
        int tex_x = n_tex * Pantalla_ImagenAnchura(img);

        Pantalla_DibujaLineaDesdeImagen(img, tex_x, i, top, bottom - top);

        /*for (int j = top; j <=bottom; j++) {
            double nj = (double) (j - top) / (bottom - top);
            int tex_y = nj * Pantalla_ImagenAltura(img);

            Pantalla_ColorTrazoDesdeImagen(img, tex_x, tex_y);
            Pantalla_DibujaPunto(i, j);
        }*/
    }
}
