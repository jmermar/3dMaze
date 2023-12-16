#include "Matematicas.h"

int imax(int a, int b) {
    return a > b ? a : b;
}

int imin(int a, int b) {
    return a < b ? a : b;
}

int iabs(int a) {
    return a > 0 ? a : -a;
}

double square(double a) {
    return a * a;
}

double mod(xy vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

double dot(xy a, xy b) {
    return a.x * b.x + a.y * b.y;
}

xy suma(xy a, xy b) {
    xy ret;
    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    return ret;
}

xy resta(xy a, xy b) {
    xy ret;
    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    return ret;
}

xy producto(xy a, double s) {
    xy ret;
    ret.x = a.x * s;
    ret.y = a.y * s;
    return ret;
}

xy interseccion(Segmento *s1, Segmento *s2) {
    xy ret;

    xy p1 = s1->s;
    xy p2 = s1->e;
    xy p3 = s2->s;
    xy p4 = s2->e;

    double t1 = p1.x * p2.y - p1.y * p2.x;
	double t2 = p3.x * p4.y - p3.y * p4.x;
	double bt = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);

	ret.x = ((p3.x - p4.x) * t1 - (p1.x - p2.x) * t2) / bt;
    ret.y = ((p3.y - p4.y) * t1 - (p1.y - p2.y) * t2) / bt;

    return ret;
}
