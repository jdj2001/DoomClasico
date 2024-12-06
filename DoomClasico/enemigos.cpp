#include <glew.h>
#include <GL/glut.h>
#include "textures.h"
#include "environment.h"
#include "enemigos.h"

// Coordenadas iniciales del enemigo
float enemigoX = 10.0f;
float enemigoZ = 10.0f;
int enemigoCurrent = 0; // Índice del sprite actual

bool moviendoDerecha = false; // Dirección del movimiento
bool moviendoIzquierda = false;

GLuint texturaEnemigo; // ID de la textura del enemigo

// Dimensiones del sprite
const int SPRITE_COLS = 7; // Número de columnas en la hoja de sprites
const int SPRITE_ROWS = 7; // Número de filas en la hoja de sprites
const float SPRITE_WIDTH = 458.0f / SPRITE_COLS;
const float SPRITE_HEIGHT = 412.0f / SPRITE_ROWS;
int frameCounter = 0;      // Contador de frames
const int framesPorSprite = 7;

// Carga de la textura del enemigo
void cargarSpriteEnemigo() {
    texturaEnemigo = loadTexture("C:/ca3.png");
}

// Dibujar el enemigo
void dibujarEnemigo() {
    float spriteWidth = 1.0f / SPRITE_COLS;
    float spriteHeight = 1.0f / SPRITE_ROWS;

    int spriteCol = enemigoCurrent % SPRITE_COLS; // Columna actual
    int spriteRow = enemigoCurrent / SPRITE_COLS; // Fila actual

    float u0 = spriteCol * spriteWidth;
    float v0 = spriteRow * spriteHeight;
    float u1 = u0 + spriteWidth;
    float v1 = v0 + spriteHeight;

    // Invertir coordenadas Y para corregir orientación
    v0 = 1.0f - v0 - spriteHeight;
    v1 = 1.0f - v1 + spriteHeight;

    // Dibujar el sprite
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaEnemigo);

    glBegin(GL_QUADS);
    glTexCoord2f(u0, v0); glVertex3f(enemigoX, 1.0f, enemigoZ - 1.0f);
    glTexCoord2f(u1, v0); glVertex3f(enemigoX + 2.0f, 1.0f, enemigoZ - 1.0f);
    glTexCoord2f(u1, v1); glVertex3f(enemigoX + 2.0f, 3.0f, enemigoZ - 1.0f);
    glTexCoord2f(u0, v1); glVertex3f(enemigoX, 3.0f, enemigoZ - 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}


// Actualizar el índice del sprite
void actualizarSprite() {
    static float tiempoAcumulado = 0.0f; // Tiempo acumulado
    float tiempoPorFrame = 0.5f;         // Duración de cada frame (en segundos)

    tiempoAcumulado += 0.016f; // Incrementa por cada frame (asume ~60 FPS)

    if (tiempoAcumulado >= tiempoPorFrame) {
        tiempoAcumulado = 0.0f;         // Reinicia el tiempo acumulado
        enemigoCurrent++;               // Cambia al siguiente frame
        enemigoCurrent %= (SPRITE_COLS * SPRITE_ROWS); // Cicla los sprites
    }

}

// Movimiento del enemigo
void moverEnemigo() {
    if (moviendoDerecha) {
        enemigoX += 0.05f; // Velocidad del movimiento
        if (enemigoX > 15.0f) { // Límite derecho
            moviendoDerecha = false;
        }
    }
    else {
        enemigoX -= 0.05f;
        if (enemigoX < 5.0f) { // Límite izquierdo
            moviendoDerecha = true;
        }
    }
}