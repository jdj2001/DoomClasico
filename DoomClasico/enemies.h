#ifndef ENEMIES_H
#define ENEMIES_H

struct Enemigo {
    float x, y, z;
    float angulo;
    float velocidad;
    int animFrame;
};

void inicializarEnemigos();
void actualizarEnemigos();
void dibujarEnemigos();
bool colisionConEnemigos(float jugadorX, float jugadorZ);

#endif