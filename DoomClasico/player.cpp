#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include "player.h"

float jugadorX = 0.0f, jugadorY = 1.0f, jugadorZ = 5.0f;
float anguloJugador = 0.0f;
float anguloVertical = 0.0f;

int mouseXAnterior = 400;
int mouseYAnterior = 300;

void inicializarJugador() {
    jugadorX = 0.0f;
    jugadorY = 1.0f;
    jugadorZ = 5.0f;
    anguloJugador = 0.0f;
    anguloVertical = 0.0f;
}

void manejarMovimientoJugador(unsigned char key) {
    const float velocidadMovimiento = 0.2f;
    if (key == 'w') { 
        jugadorX += velocidadMovimiento * sin(anguloJugador);
        jugadorZ -= velocidadMovimiento * cos(anguloJugador);
    }
    if (key == 's') {  
        jugadorX -= velocidadMovimiento * sin(anguloJugador);
        jugadorZ += velocidadMovimiento * cos(anguloJugador);
    }
    if (key == 'a') {  
        jugadorX -= velocidadMovimiento * cos(anguloJugador);
        jugadorZ -= velocidadMovimiento * sin(anguloJugador);
    }
    if (key == 'd') {  
        jugadorX += velocidadMovimiento * cos(anguloJugador);
        jugadorZ += velocidadMovimiento * sin(anguloJugador);
    }
}

void manejarMovimientoMouse(int x, int y) {
    const float sensibilidad = 0.002f;  

    float deltaX = (x - mouseXAnterior) * sensibilidad;
    anguloJugador += deltaX;

    float deltaY = (y - mouseYAnterior) * sensibilidad;
    anguloVertical -= deltaY;

    if (anguloVertical > 90.0f) anguloVertical = 90.0f; 
    if (anguloVertical < -90.0f) anguloVertical = -90.0f;

    mouseXAnterior = x;
    mouseYAnterior = y;

    glutPostRedisplay();
}

void actualizarCamara() {
    gluLookAt(jugadorX, jugadorY + 1.0f, jugadorZ,
        jugadorX + sin(anguloJugador), jugadorY + sin(anguloVertical) + 1.0f, jugadorZ - cos(anguloJugador),
        0.0f, 1.0f, 0.0f);
}
