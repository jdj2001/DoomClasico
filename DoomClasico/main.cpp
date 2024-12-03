#include <Windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "environment.h"
#include "player.h"
#include <iostream>
#include "weapon.h"
#include "game.h"
#include <SDL.h>
#include <SDL_mixer.h>

/*void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0f, 800.0f / 600.0f, 0.1f, 500.0f);
    glMatrixMode(GL_MODELVIEW);


    glLoadIdentity();

    actualizarCamara();
    dibujarMapa();
    //actualizarArma(float jugadorX, float jugadorY, float jugadorZ, float anguloJugador);
    actualizarArma();
    //actualizarArma(jugadorX, jugadorY, jugadorZ, anguloJugador);

    glutSwapBuffers();
}*/
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0f, 800.0f / 600.0f, 0.1f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    actualizarCamara();
    dibujarMapa();
    actualizarArma();
    renderizarEscena();

    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y) {
    manejarMovimientoJugador(key);
    glutPostRedisplay();
}

void inicializarMouse() {
    glutWarpPointer(400, 300);
    mouseXAnterior = 400;
    mouseYAnterior = 300;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Doom Clasico");

    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    /*glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);*/

    inicializarEntorno();
    inicializarJugador();
    inicializarArma();

    inicializarMouse();
	glutMouseFunc(manejarDisparo);
    glutPassiveMotionFunc(manejarMovimientoMouse);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDepthFunc(GL_LESS);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // Modo de mezcla
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_CULL_FACE);  
    glFrontFace(GL_CCW);     
    glCullFace(GL_BACK);     
    glShadeModel(GL_SMOOTH);


    glutMainLoop();
    return 0;
}
