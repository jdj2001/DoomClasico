#include <GL/glew.h>
#include <GL/glut.h>
#include "textures.h"
#include "environment.h"
#include "enemigos.h"
#include "player.h"
#include "collision.h"
#include "vida.h"

extern Vida vida;

float enemigoX = 10.0f;
float enemigoZ = 10.0f;
int enemigoCurrent = 0;

bool moviendoDerecha = false;
bool moviendoIzquierda = false;

GLuint texturaEnemigo;

const int SPRITE_COLS = 7;
const int SPRITE_ROWS = 7;
const float SPRITE_WIDTH = 458.0f / SPRITE_COLS;
const float SPRITE_HEIGHT = 412.0f / SPRITE_ROWS;
int frameCounter = 0;
const int framesPorSprite = 7;

void cargarSpriteEnemigo() {
    texturaEnemigo = loadTexture("C:/Enemigo1.png");
}

void dibujarEnemigo() {
    float spriteWidth = 1.0f / SPRITE_COLS;
    float spriteHeight = 1.0f / SPRITE_ROWS;

    int spriteCol = enemigoCurrent % SPRITE_COLS;
    int spriteRow = enemigoCurrent / SPRITE_COLS;

    float u0 = spriteCol * spriteWidth;
    float v0 = spriteRow * spriteHeight;
    float u1 = u0 + spriteWidth;
    float v1 = v0 + spriteHeight;

    v0 = 1.0f - v0 - spriteHeight;
    v1 = 1.0f - v1 + spriteHeight;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaEnemigo);

    glBegin(GL_QUADS);
    glTexCoord2f(u0, v1); glVertex3f(enemigoX, 1.0f, enemigoZ - 1.0f);
    glTexCoord2f(u1, v1); glVertex3f(enemigoX + 2.0f, 1.0f, enemigoZ - 1.0f);
    glTexCoord2f(u1, v0); glVertex3f(enemigoX + 2.0f, 3.0f, enemigoZ - 1.0f);
    glTexCoord2f(u0, v0); glVertex3f(enemigoX, 3.0f, enemigoZ - 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void actualizarSprite() {
    static float tiempoAcumulado = 0.0f;
    float tiempoPorFrame = 0.5f;

    tiempoAcumulado += 0.016f;

    if (tiempoAcumulado >= tiempoPorFrame) {
        tiempoAcumulado = 0.0f;
        enemigoCurrent++;
        enemigoCurrent %= (SPRITE_COLS * SPRITE_ROWS);
    }
}

void moverEnemigo() {
    if (moviendoDerecha) {
        enemigoX += 0.05f;
        if (enemigoX > 15.0f) {
            moviendoDerecha = false;
        }
    }
    else {
        enemigoX -= 0.05f;
        if (enemigoX < 5.0f) {
            moviendoDerecha = true;
        }
    }

    if (checkCollision(enemigoX, enemigoZ, jugadorX, jugadorZ, 1.0f)) {
        vida.setHealth(vida.getHealth() - 1);
    }
}