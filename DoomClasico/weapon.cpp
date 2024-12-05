#include <GL/glew.h>
#include <GL/glut.h>
#include "weapon.h"
#include "sound.h"
#include "textures.h"
#include <iostream>

bool disparando = false;
int frameDisparo = 0;
GLuint spriteArma;

float textureWidth = 590.0f;
float textureHeight = 626.0f;

struct Animacion {
    float texCoordLeft, texCoordRight, texCoordBottom, texCoordTop;
};

Animacion posicionNormalAnim = {
    3.0f / textureWidth, (3.0f + 116.0f) / textureWidth,
    (105.0f + 95.0f) / textureHeight, 105.0f / textureHeight
};

Animacion disparoAnimaciones[] = {
    //{3.0f / textureWidth, (3.0f + 116.0f) / textureWidth, (105.0f + 95.0f) / textureHeight, 105.0f / textureHeight},
    {122.0f / textureWidth, (122.0f + 150.0f) / textureWidth, (57.0f + 143.0f) / textureHeight, 57.0f / textureHeight},
    {275.0f / textureWidth, (275.0f + 94.0f) / textureWidth, (17.0f + 183.0f) / textureHeight, 17.0f / textureHeight},
    {372.0f / textureWidth, (372.0f + 127.0f) / textureWidth, (37.0f + 163.0f) / textureHeight, 37.0f / textureHeight}
    //{3.0f / textureWidth, (3.0f + 116.0f) / textureWidth, (105.0f + 95.0f) / textureHeight, 105.0f / textureHeight}
};

void inicializarArma() {
    spriteArma = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/personajes/WeaponsDoomAlpha_1.png");
    if (spriteArma == 0) {
        std::cerr << "Error: Textura del arma no cargada correctamente." << std::endl;
        return;
    }

    glBindTexture(GL_TEXTURE_2D, spriteArma);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}


void dibujarSprite(Animacion anim, float x, float y, float width, float height) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, spriteArma);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ONE, GL_ONE);
    //glBlendFunc(GL_SRC_COLOR, GL_ONE);

    glBegin(GL_QUADS);
    glTexCoord2f(anim.texCoordLeft, anim.texCoordBottom); glVertex2f(x, y);
    glTexCoord2f(anim.texCoordRight, anim.texCoordBottom); glVertex2f(x + width, y);
    glTexCoord2f(anim.texCoordRight, anim.texCoordTop); glVertex2f(x + width, y + height);
    glTexCoord2f(anim.texCoordLeft, anim.texCoordTop); glVertex2f(x, y + height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

/*void actualizarArma() {
    float ancho = 300.0f;
    float alto = ancho * (95.0f / 116.0f);
    float posicionX = (800.0f - ancho) / 2.0f;
    float posicionY = 0.0f;

    if (disparando) {
        // Recorremos todas las animaciones de disparo en un ciclo for
        for (int i = 0; i < 3; i++) {
            if (frameDisparo == i) {
                dibujarSprite(disparoAnimaciones[i], posicionX, posicionY, ancho, alto);
                frameDisparo++;
                break; // Salimos del ciclo para evitar avanzar más de un frame por actualización
            }
        }

        // Si hemos completado todas las animaciones, regresamos a la posición normal
        if (frameDisparo == 3) {
            disparando = false;
            frameDisparo = 0;
            //dibujarSprite(posicionNormalAnim, posicionX, posicionY, ancho, alto);
        }
    }
    else {
        // Posición normal del arma
        dibujarSprite(posicionNormalAnim, posicionX, posicionY, ancho, alto);
    }
}*/
void actualizarArma() {
    float ancho = 300.0f;
    float alto = ancho * (95.0f / 116.0f);
    float posicionX = (800.0f - ancho) / 2.0f;
    float posicionY = 0.0f;

    if (disparando) {
        // Dibuja el frame actual de disparo
        dibujarSprite(disparoAnimaciones[frameDisparo], posicionX, posicionY, ancho, alto);
    }
    else {
        // Dibuja la posición normal del arma
        dibujarSprite(posicionNormalAnim, posicionX, posicionY, ancho, alto);
    }
}
void animarDisparo(int value) {
    if (disparando) {
        frameDisparo++;

        if (frameDisparo >= 3) {
            disparando = false;
            frameDisparo = 0;
        }
        else {
            glutTimerFunc(200, animarDisparo, 0);
        }
        glutPostRedisplay();
    }
}
void manejarDisparo(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!disparando) {
            disparando = true;
            frameDisparo = 0;
            animarDisparo(0);
            reproducirSonidoDisparo();
        }
    }
    std::cerr << "Disparo manejado: " << (disparando ? "Sí" : "No")
        << ", Frame: " << frameDisparo << std::endl;
}



/*void manejarDisparo(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        disparando = true;
        //frameDisparo = 0;
        //actualizarArma();
        glutPostRedisplay();
        
    }
    std::cerr << "Disparo manejado: " << (disparando ? "Si" : "No")
              << ", Frame: " << frameDisparo << std::endl;
}*/
