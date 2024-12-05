#ifndef WEAPON_H
#define WEAPON_H

#include <GL/glew.h>

void inicializarArma();

void actualizarArma();

void manejarDisparo(int button, int state, int x, int y);

#endif