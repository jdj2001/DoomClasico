#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include "enemies.h"
#include "textures.h"
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

GLuint texturaZombie;

struct Animacion {
    float texCoordLeft, texCoordRight, texCoordBottom, texCoordTop;
};

Animacion zombieFrontal[] = {
    {3.0f / 128.0f, (3.0f + 41.0f) / 128.0f, (1.0f + 55.0f) / 256.0f, 1.0f / 256.0f},
    {47.0f / 128.0f, (47.0f + 37.0f) / 128.0f, (1.0f + 55.0f) / 256.0f, 1.0f / 256.0f},
    {87.0f / 128.0f, (87.0f + 38.0f) / 128.0f, (1.0f + 55.0f) / 256.0f, 1.0f / 256.0f}
};

Animacion zombieLateral[] = {
    {3.0f / 128.0f, (3.0f + 43.0f) / 128.0f, (116.0f + 53.0f) / 256.0f, 116.0f / 256.0f},
    {49.0f / 128.0f, (49.0f + 36.0f) / 128.0f, (114.0f + 55.0f) / 256.0f, 114.0f / 256.0f},
    {88.0f / 128.0f, (88.0f + 37.0f) / 128.0f, (115.0f + 55.0f) / 256.0f, 115.0f / 256.0f}
};

Animacion zombieTrasero[] = {
    {3.0f / 128.0f, (3.0f + 36.0f) / 128.0f, (235.0f + 51.0f) / 256.0f, 235.0f / 256.0f},
    {42.0f / 128.0f, (42.0f + 35.0f) / 128.0f, (232.0f + 54.0f) / 256.0f, 232.0f / 256.0f},
    {80.0f / 128.0f, (80.0f + 34.0f) / 128.0f, (231.0f + 55.0f) / 256.0f, 231.0f / 256.0f}
};

const int NUM_ENEMIGOS = 2;
Enemigo enemigos[NUM_ENEMIGOS];

void inicializarEnemigos() {
    texturaZombie = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/personajes/Zombie.png");
    enemigos[0] = { 9.0f, 0.0f, 4.0f, 0.0f, 0 };
    enemigos[1] = { 9.0f, 0.0f, 6.0f, 0.0f, 0 };
}

void actualizarEnemigos() {
    for (int i = 0; i < NUM_ENEMIGOS; i++) {
        enemigos[i].animFrame = (enemigos[i].animFrame + 1) % 3;
    }
}

/*void actualizarEnemigos() {
    for (int i = 0; i < NUM_ENEMIGOS; i++) {
        // Movimiento básico
        enemigos[i].x += enemigos[i].velocidad * cos(enemigos[i].angulo);
        enemigos[i].z += enemigos[i].velocidad * sin(enemigos[i].angulo);

        // Cambiar dirección si se acerca al borde del área
        if (enemigos[i].x < 8.0f || enemigos[i].x > 10.0f || enemigos[i].z < 3.0f || enemigos[i].z > 7.0f) {
            enemigos[i].angulo += M_PI / 2.0f;
        }

        // Actualizar animación
        enemigos[i].animFrame = (enemigos[i].animFrame + 1) % 3;
    }
}*/

void dibujarZombie3D(Enemigo enemigo) {
    glPushMatrix();
    glTranslatef(enemigo.x + 0.5f, 0.0f, enemigo.z + 0.5f);

    Animacion frontal = zombieFrontal[enemigo.animFrame];
    Animacion lateral = zombieLateral[enemigo.animFrame];
    Animacion trasero = zombieTrasero[enemigo.animFrame];

    glBindTexture(GL_TEXTURE_2D, texturaZombie);

    // Cara frontal
    glBegin(GL_QUADS);
    glTexCoord2f(frontal.texCoordLeft, frontal.texCoordBottom); glVertex3f(-0.5f, 0.0f, 0.5f);
    glTexCoord2f(frontal.texCoordRight, frontal.texCoordBottom); glVertex3f(0.5f, 0.0f, 0.5f);
    glTexCoord2f(frontal.texCoordRight, frontal.texCoordTop); glVertex3f(0.5f, 1.0f, 0.5f);
    glTexCoord2f(frontal.texCoordLeft, frontal.texCoordTop); glVertex3f(-0.5f, 1.0f, 0.5f);
    glEnd();

    // Cara trasera
    glBegin(GL_QUADS);
    glTexCoord2f(trasero.texCoordLeft, trasero.texCoordBottom); glVertex3f(0.5f, 0.0f, -0.5f);
    glTexCoord2f(trasero.texCoordRight, trasero.texCoordBottom); glVertex3f(-0.5f, 0.0f, -0.5f);
    glTexCoord2f(trasero.texCoordRight, trasero.texCoordTop); glVertex3f(-0.5f, 1.0f, -0.5f);
    glTexCoord2f(trasero.texCoordLeft, trasero.texCoordTop); glVertex3f(0.5f, 1.0f, -0.5f);
    glEnd();

    // Cara lateral izquierda
    glBegin(GL_QUADS);
    glTexCoord2f(lateral.texCoordLeft, lateral.texCoordBottom); glVertex3f(-0.5f, 0.0f, -0.5f);
    glTexCoord2f(lateral.texCoordRight, lateral.texCoordBottom); glVertex3f(-0.5f, 0.0f, 0.5f);
    glTexCoord2f(lateral.texCoordRight, lateral.texCoordTop); glVertex3f(-0.5f, 1.0f, 0.5f);
    glTexCoord2f(lateral.texCoordLeft, lateral.texCoordTop); glVertex3f(-0.5f, 1.0f, -0.5f);
    glEnd();

    //mirror
    glBegin(GL_QUADS);
    glTexCoord2f(lateral.texCoordRight, lateral.texCoordBottom); glVertex3f(0.5f, 0.0f, 0.5f);
    glTexCoord2f(lateral.texCoordLeft, lateral.texCoordBottom); glVertex3f(0.5f, 0.0f, -0.5f);
    glTexCoord2f(lateral.texCoordLeft, lateral.texCoordTop); glVertex3f(0.5f, 1.0f, -0.5f);
    glTexCoord2f(lateral.texCoordRight, lateral.texCoordTop); glVertex3f(0.5f, 1.0f, 0.5f);
    glEnd();

    glPopMatrix();
}

void dibujarEnemigos() {
    for (int i = 0; i < NUM_ENEMIGOS; i++) {
        dibujarZombie3D(enemigos[i]);
    }
}

/*void dibujarEnemigos() {
    glBindTexture(GL_TEXTURE_2D, texturaZombie);
    for (int i = 0; i < NUM_ENEMIGOS; i++) {
        Animacion anim = zombieFrontal[enemigos[i].animFrame];

        glPushMatrix();
        glTranslatef(enemigos[i].x, enemigos[i].y, enemigos[i].z);
        glBegin(GL_QUADS);
        glTexCoord2f(anim.texCoordLeft, anim.texCoordBottom); glVertex3f(-0.5f, 0.0f, 0.0f);
        glTexCoord2f(anim.texCoordRight, anim.texCoordBottom); glVertex3f(0.5f, 0.0f, 0.0f);
        glTexCoord2f(anim.texCoordRight, anim.texCoordTop); glVertex3f(0.5f, 1.0f, 0.0f);
        glTexCoord2f(anim.texCoordLeft, anim.texCoordTop); glVertex3f(-0.5f, 1.0f, 0.0f);
        glEnd();
        glPopMatrix();
    }
}*/

bool colisionConEnemigos(float jugadorX, float jugadorZ) {
    const float radioColision = 0.5f;

    for (int i = 0; i < NUM_ENEMIGOS; i++) {
        float distancia = sqrt(pow(jugadorX - enemigos[i].x, 2) + pow(jugadorZ - enemigos[i].z, 2));
        if (distancia < radioColision) {
            return true;  
        }
    }
    return false;
}
