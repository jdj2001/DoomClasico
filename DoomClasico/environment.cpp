#include <GL/glew.h>
#include <GL/glut.h>
#include "textures.h"
#include "environment.h"
#include <string>

const int MAP_SIZE = 20;

const char PARED = 'P';
const char PARED2 = 'P3';
const char SUELO = 'S';
const char OBJETO_INTERACTIVO = 'I';
const char HANGAR = 'H';
const char CUARTO_SECRETO = 'C';
const char SALA_DEL_JEFE = 'B';

const std::string MAP[MAP_SIZE][MAP_SIZE] = {
    {"P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P"},
    {"P", "S", "S", "S", "S", "S", "D", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "S", "S", "S", "S", "S", "D", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "S", "S", "S", "S", "S", "P", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "S", "S", "S", "S", "S", "P", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "S", "S", "S", "S", "S", "P", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "P", "P", "P", "D", "D", "P", "P", "P", "P", "P", "P", "P", "D", "D", "P", "P", "P", "P", "P"},
    {"P", "S", "S", "S", "S", "S", "D", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "S", "S", "S", "S", "S", "D", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "S", "S", "S", "S", "S", "P", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "S", "S", "S", "S", "S", "P", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "D", "D", "D", "D", "D", "P", "P", "P", "P", "P", "P", "P", "D", "D", "D", "D", "D", "D", "P"},
    {"P", "S", "S", "S", "S", "S", "D", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "S", "S", "S", "S", "S", "D", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "S", "S", "S", "S", "S", "P", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "S", "S", "S", "S", "S", "P", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "S", "S", "S", "S", "S", "P", "P", "P", "P", "P", "P", "P", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "S", "S", "S", "S", "S", "P", "P", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "S", "S", "S", "S", "S", "P", "P", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "S", "P"},
    {"P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P"}
};

void inicializarEntorno() {
    loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/tn116.jpg"); // Piso
    loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/paredes/tn373.jpg"); // Pared
}

void dibujarMapa() {
    glEnable(GL_TEXTURE_2D);

    const int techo = 5;

    GLuint texturaSuelo = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/tn116.jpg");
    GLuint texturaPared = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/paredes/tn373.jpg");
    GLuint texturaTecho = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/techo/techo_bloque.png");

    for (int x = 0; x < MAP_SIZE; x++) {
        for (int z = 0; z < MAP_SIZE; z++) {
            for (int y = 0; y < techo; y++) {
                if (MAP[x][z] == "P") {
                    //PAREDES QUE SE VEN DE MANERA FRONTAL Y TRASERA
                    glBindTexture(GL_TEXTURE_2D, texturaPared);
                    glBegin(GL_QUADS);

                    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + 1.0f, z);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, y + 1.0f, z);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, y, z);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z);

                    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + 1.0f);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + 1.0f, z + 1.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + 1.0f, z);

                    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + 1.0, y + 1.0f, z + 1.0f);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + 1.0f, z + 1.0f);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + 1.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + 1.0, y, z + 1.0f);

                    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + 1, y, z + 1.0f);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1, y, z);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1, y + 1.0f, z);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + 1, y + 1.0f, z + 1.0f);

                    // Cara inferior (suelo)
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, y, z);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, y, z + 1.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z + 1.0f);

                    // Cara superior (techo)
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + 1.0f, z);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, y + 1.0f, z);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + 1.0f, z + 1.0f);

                    glEnd();
                }
            }
            if (MAP[x][z] == "D") {
                for (int y = 3; y < techo; y++) {
                    glBindTexture(GL_TEXTURE_2D, texturaPared);
                    glBegin(GL_QUADS);

                    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + 1.0f, z);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, y + 1.0f, z);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, y, z);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z);

                    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + 1.0f);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + 1.0f, z + 1.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + 1.0f, z);

                    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + 1.0, y + 1.0f, z + 1.0f);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + 1.0f, z + 1.0f);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + 1.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + 1.0, y, z + 1.0f);

                    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + 1, y, z + 1.0f);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1, y, z);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1, y + 1.0f, z);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + 1, y + 1.0f, z + 1.0f);

                    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, y, z);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, y, z + 1.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, z + 1.0f);

                    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + 1.0f, z);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, y + 1.0f, z);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + 1.0f, z + 1.0f);

                    glEnd();
                }
                glBindTexture(GL_TEXTURE_2D, texturaSuelo);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            if (MAP[x][z] == "S") {
                glBindTexture(GL_TEXTURE_2D, texturaSuelo);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            if (MAP[x][z] == "S") {
                glBindTexture(GL_TEXTURE_2D, texturaTecho);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, techo + 1.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, techo + 1.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, techo + 1.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, techo + 1.0f, z);

                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, techo, z);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, techo, z);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, techo, z + 1.0f);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, techo, z + 1.0f);
                glEnd();
            }
        }
    }
    glDisable(GL_TEXTURE_2D);
}