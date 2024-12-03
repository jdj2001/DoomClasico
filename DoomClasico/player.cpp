#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include "player.h"
#include "textures.h"
#include "weapon.h"
#include "enemies.h"
#include "collision.h"
#include "environment.h"

float jugadorX = 2.5f, jugadorY = 0.5f, jugadorZ = 2.5f;
float anguloJugador = 0.0f;  
float anguloVertical = 0.0f; 

int mouseXAnterior = 400;
int mouseYAnterior = 300;

void inicializarJugador() {
    jugadorX = 2.5f;
    jugadorY = 0.5f;
    jugadorZ = 2.5f;
    anguloJugador = 0.0f;
    anguloVertical = 0.0f;
}

void manejarMovimientoJugador(unsigned char key) {
    const float velocidadMovimiento = 0.2f;
    float nuevoX = jugadorX, nuevoZ = jugadorZ;

    if (key == 'w') {
        nuevoX += velocidadMovimiento * sin(anguloJugador);
        nuevoZ -= velocidadMovimiento * cos(anguloJugador);
    }
    if (key == 's') {
        nuevoX -= velocidadMovimiento * sin(anguloJugador);
        nuevoZ += velocidadMovimiento * cos(anguloJugador);
    }
    if (key == 'a') {
        nuevoX -= velocidadMovimiento * cos(anguloJugador);
        nuevoZ -= velocidadMovimiento * sin(anguloJugador);
    }
    if (key == 'd') {
        nuevoX += velocidadMovimiento * cos(anguloJugador);
        nuevoZ += velocidadMovimiento * sin(anguloJugador);
    }

    if (!colisionConMapa(nuevoX, nuevoZ)) {
        jugadorX = nuevoX;
        jugadorZ = nuevoZ;
    }
}

void manejarMovimientoMouse(int x, int y) {
    const float sensibilidad = 0.008f;

    float deltaX = (x - mouseXAnterior) * sensibilidad;
    anguloJugador += deltaX;

    float deltaY = (y - mouseYAnterior) * sensibilidad;
    anguloVertical -= deltaY;

    if (anguloVertical > 1.4f) anguloVertical = 1.4f;  
    if (anguloVertical < -1.4f) anguloVertical = -1.4f; 

    mouseXAnterior = x;
    mouseYAnterior = y;

    glutPostRedisplay();
}

void actualizarCamara() {
    gluLookAt(
        jugadorX, jugadorY + 1.0f, jugadorZ,
        jugadorX + sin(anguloJugador), jugadorY + sin(anguloVertical) + 1.0f, jugadorZ - cos(anguloJugador),
        0.0f, 1.0f, 0.0f
    );
    //actualizarArma();
}

