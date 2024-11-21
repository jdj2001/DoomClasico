#include <GL/glew.h>
#include <GL/glut.h>
#include "textures.h"
#include "environment.h"

const int MAP_SIZE = 10;
const char MAP[MAP_SIZE][MAP_SIZE] = {
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P'},
    {'P', ' ', 'S', 'S', 'S', 'S', 'S', 'S', ' ', 'P'},
    {'P', ' ', 'S', 'S', 'S', 'S', 'S', 'S', ' ', 'P'},
    {'P', ' ', 'S', 'S', 'S', 'S', 'S', 'S', ' ', 'P'},
    {'P', ' ', 'S', 'S', 'S', 'S', 'S', 'S', ' ', 'P'},
    {'P', ' ', 'S', 'S', 'S', 'S', 'S', 'S', ' ', 'P'},
    {'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P'},
    {'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
};

void inicializarEntorno() {
    loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/tn116.jpg"); // Piso
    loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/paredes/tn373.jpg"); // Pared
}

void dibujarMapa() {
    glEnable(GL_TEXTURE_2D);

    GLuint texturaSuelo = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/tn116.jpg");
    GLuint texturaPared = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/paredes/tn373.jpg");

    for (int x = 0; x < MAP_SIZE; x++) {
        for (int z = 0; z < MAP_SIZE; z++) {
            if (MAP[x][z] == 'S') {
                glBindTexture(GL_TEXTURE_2D, texturaSuelo);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                
                glEnd();
            }
            if (MAP[x][z] == 'P') {
                glBindTexture(GL_TEXTURE_2D, texturaPared);
                glBegin(GL_QUADS);
                // CARA FRONTAL
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 1.0f, z);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 1.0f, z);
                //CARA TRASERA
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 1.0f, z + 1.0f);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 1.0f, z + 1.0f);
                glEnd();
            }
        }
    }

    glDisable(GL_TEXTURE_2D);
}




