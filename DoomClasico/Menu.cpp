#include <GL/glew.h>
#include <GL/glut.h>
#include "Menu.h"
#include "stb_image.h"
#include <iostream>
#include "textures.h"

GLuint texturaFondo;
const int anchoVentana = 1280;
const int altoVentana = 720;

struct Boton {
    float x, y, ancho, alto;
    std::string etiqueta;
};

Boton botones[] = {
    {540, 400, 200, 50, "Iniciar Juego"},
    {540, 300, 200, 50, "Instrucciones"},
    {540, 200, 200, 50, "Salir del Juego"}
};

GameState estadoActual = MENU;
bool instruccionesVisibles = false;

void dibujarFondo() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaFondo);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(anchoVentana, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(anchoVentana, altoVentana);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, altoVentana);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void dibujarTextoCentrado(float x, float y, const std::string& texto, void* fuente, float escala = 1.0f) {
    float anchoTexto = 0;
    for (char c : texto) {
        anchoTexto += glutBitmapWidth(fuente, c) * escala;
    }

    float xCentrado = x - (anchoTexto / 2.0f);
    float yCentrado = y - (10.0f * escala);

    glRasterPos2f(xCentrado, yCentrado);
    for (char c : texto) {
        glutBitmapCharacter(fuente, c);
    }
}

void dibujarBoton(const Boton& boton) {
    glColor3f(0.4f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(boton.x, boton.y);
    glVertex2f(boton.x + boton.ancho, boton.y);
    glVertex2f(boton.x + boton.ancho, boton.y - boton.alto);
    glVertex2f(boton.x, boton.y - boton.alto);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    dibujarTextoCentrado(boton.x + boton.ancho / 2.0f, boton.y - boton.alto / 2.0f, boton.etiqueta, GLUT_BITMAP_HELVETICA_18);
}

void inicializarMenu() {
    texturaFondo = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/doomfondo.png");
}

void renderizarTexto(const char* texto, float x, float y) {
    glRasterPos2f(x, y);
    for (int i = 0; texto[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]); 
    }
}

void dibujarMenu() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(botones[0].x, botones[0].y);
    glVertex2f(botones[0].x + botones[0].ancho, botones[0].y);
    glVertex2f(botones[0].x + botones[0].ancho, botones[0].y + botones[0].alto);
    glVertex2f(botones[0].x, botones[0].y + botones[0].alto);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    renderizarTexto("Iniciar Juego", botones[0].x + 10, botones[0].y + 10);

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(botones[1].x, botones[1].y);
    glVertex2f(botones[1].x + botones[1].ancho, botones[1].y);
    glVertex2f(botones[1].x + botones[1].ancho, botones[1].y + botones[1].alto);
    glVertex2f(botones[1].x, botones[1].y + botones[1].alto);
    glEnd();

    renderizarTexto("Instrucciones", botones[1].x + 10, botones[1].y + 10);

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(botones[2].x, botones[2].y);
    glVertex2f(botones[2].x + botones[2].ancho, botones[2].y);
    glVertex2f(botones[2].x + botones[2].ancho, botones[2].y + botones[2].alto);
    glVertex2f(botones[2].x, botones[2].y + botones[2].alto);
    glEnd();

    renderizarTexto("Salir", botones[2].x + 10, botones[2].y + 10);

    if (instruccionesVisibles) {
        renderizarTexto("Instrucciones del juego aquí...", 100, 300);
    }

    glutSwapBuffers();
}

void dibujarInstrucciones() {
    glClear(GL_COLOR_BUFFER_BIT);
    dibujarFondo();

    glColor3f(1.0f, 0.8f, 0.0f);
    dibujarTextoCentrado(anchoVentana / 2.0f, 600.0f, "INSTRUCCIONES", GLUT_BITMAP_TIMES_ROMAN_24);

    glColor3f(1.0f, 1.0f, 1.0f);
    dibujarTextoCentrado(anchoVentana / 2.0f, 500.0f, "Objetivo: Sobrevive a los demonios y recolecta objetos.", GLUT_BITMAP_HELVETICA_18);
    dibujarTextoCentrado(anchoVentana / 2.0f, 450.0f, "Controles: Usa W, A, S, D para moverte y el ratón para disparar.", GLUT_BITMAP_HELVETICA_18);
    dibujarTextoCentrado(anchoVentana / 2.0f, 400.0f, "Salud: Evita los ataques enemigos para conservar vida.", GLUT_BITMAP_HELVETICA_18);

    Boton botonVolver = { 540, 150, 200, 50, "Volver" };
    dibujarBoton(botonVolver);

    glFlush();
    glutSwapBuffers();
}

void manejarMouseMenu(int boton, int estado, int x, int y) {
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        float oglX = static_cast<float>(x);
        float oglY = altoVentana - static_cast<float>(y);

        if (!instruccionesVisibles) {
            if (oglX >= botones[0].x && oglX <= botones[0].x + botones[0].ancho &&
                oglY >= botones[0].y - botones[0].alto && oglY <= botones[0].y) {
                estadoActual = GAME;
            }
            else if (oglX >= botones[1].x && oglX <= botones[1].x + botones[1].ancho &&
                oglY >= botones[1].y - botones[1].alto && oglY <= botones[1].y) {
                instruccionesVisibles = true;
                glutPostRedisplay();
            }
            else if (oglX >= botones[2].x && oglX <= botones[2].x + botones[2].ancho &&
                oglY >= botones[2].y - botones[2].alto && oglY <= botones[2].y) {
                exit(0);
            }
        }
        else {
            if (oglX >= 540 && oglX <= 740 && oglY >= 100 && oglY <= 150) {
                instruccionesVisibles = false;
                glutPostRedisplay();
            }
        }
    }
}