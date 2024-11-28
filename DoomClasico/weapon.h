#ifndef WEAPON_H
#define WEAPON_H

#include <GL/glew.h>

// Inicializar el arma y cargar las texturas necesarias
void inicializarArma();

// Dibujar y actualizar el arma en su estado actual
void actualizarArma();
//void actualizarArma(float jugadorX, float jugadorY, float jugadorZ, float anguloJugador);

// Manejar el evento de disparo (clic del mouse)
void manejarDisparo(int button, int state, int x, int y);

#endif // WEAPON_H