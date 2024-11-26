#include <GL/glew.h>
#include <GL/glut.h>
#include "environment.h"
#include "player.h"
#include <iostream>

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0f, 800.0f / 600.0f, 0.1f, 500.0f);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    actualizarCamara();
    dibujarMapa();

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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Doom Clasico");

    glEnable(GL_DEPTH_TEST);

    inicializarEntorno();
    inicializarJugador();

    inicializarMouse();
    glutPassiveMotionFunc(manejarMovimientoMouse);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    //glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_CULL_FACE);  
    glFrontFace(GL_CCW);     
    glCullFace(GL_BACK);     
    glShadeModel(GL_SMOOTH); 


    glutMainLoop();
    return 0;
}
