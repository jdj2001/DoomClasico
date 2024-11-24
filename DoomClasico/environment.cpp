#include <GL/glew.h>
#include <GL/glut.h>
#include "textures.h"
#include "environment.h"

const int MAP_SIZE = 50;

/*const long MAP[MAP_SIZE][MAP_SIZE] = {
    {'P3', 'P3', 'P3', 'P3', 'P3', 'P3', 'P3', 'P3', 'P3', 'P'}, 
    {'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P'},
    {'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P'}, 
    {'P', ' ', 'S', 'S', 'S', 'S', 'S', 'S', ' ', 'P'},
    {'P', ' ', 'S', 'S', 'I', 'I', 'S', 'S', ' ', 'P'}, 
    {'P', ' ', 'S', 'S', 'S', 'S', 'S', 'S', ' ', 'P'},
    {'P', ' ', 'S', 'S', 'S', 'S', 'S', 'S', ' ', 'P'},
    {'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P'},
    {'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P'},
    {'P3', 'P3', 'P3', 'P3', 'P3', 'P3', 'P3', 'P3', 'P3', 'P'},//
};
*/
const char PARED = 'P';
const char SUELO = 'S';
const char OBJETO_INTERACTIVO = 'I';
const char HANGAR = 'H';
const char CUARTO_SECRETO = 'C';
const char SALA_DEL_JEFE = 'B';

const char MAP[MAP_SIZE][MAP_SIZE] = {
    "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
    "PSSSSSSSSSSSSSSSSSSSSSSPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSSSSSSSSSSSSSPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSSHHHHHHHHHHHPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSSHHHHHHHHHHHPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSSHHHHHHHHHHHPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSHHHHHHHHHHHHPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSHHHHHHHHHHHHPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSHHHHHHHHHHHHPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSSSSSSSSSSSSSPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSSSSSSSSSSSSSPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSSSSSSSSSSSSSPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSSSSSSSSSSSSSPPPPPPSSSSSSSSSSSSSSSSP3",
    "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
    "P3SSSSSSSSSSSSSSSSSSSSSSPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSSSSSSSSSSSSSPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSSSSSSSSSSSSSPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSQQQQQQQQQQQQPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSQQQQQQQQQQQQPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSQQQQQQQQQQQQPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSQQQQQQQQQQQQPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSQQQQQQQQQQQQPPPPPPSSSSSSSSSSSSSSSSP3",
    "P3SSSSSSSSSSQQQQQQQQQQQQPPPPPPSSSSSSSSSSSSSSSSP3",
    "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
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
                //PAREDES QUE SE VEN DE MANERA FRONTAL Y TRASERA
                glBindTexture(GL_TEXTURE_2D, texturaPared);

                glBegin(GL_QUADS);
                
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 1.0f, z);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 1.0f, z);

                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 1.0f, z);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 1.0f, z);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z);
                
                glEnd();
            }
            
            if (MAP[x][z] == 'P3') {
                //PAREDES QUE SE VEN LATERALMENTE (IZQUIERDA Y DERECHA)
                glBindTexture(GL_TEXTURE_2D, texturaPared);

                glBegin(GL_QUADS);

                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x, 1.0f, z + 1.0f);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 1.0f, z);

                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 1.0f, z);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x, 1.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            
        }
    }
    glDisable(GL_TEXTURE_2D);
}
/*void dibujarMapa() {
    glEnable(GL_TEXTURE_2D);

    // Asocia texturas a variables
    GLuint texturaSuelo = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/tn116.jpg");
    GLuint texturaPared = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/paredes/tn373.jpg");
    /*GLuint texturaInteractivo = loadTexture("textures/objeto_interactivo.jpg");
    GLuint texturaHangar = loadTexture("textures/hangar.jpg");
    GLuint texturaCuartoSecreto = loadTexture("textures/cuarto_secreto.jpg");
    GLuint texturaSalaJefe = loadTexture("textures/sala_jefe.jpg");

    for (int x = 0; x < MAP_SIZE; x++) {
        for (int z = 0; z < MAP_SIZE; z++) {
            switch (MAP[x][z]) {
            case SUELO:
                glBindTexture(GL_TEXTURE_2D, texturaSuelo);
                break;
            case PARED:
                glBindTexture(GL_TEXTURE_2D, texturaPared);
                break;
            /*case OBJETO_INTERACTIVO:
                glBindTexture(GL_TEXTURE_2D, texturaInteractivo);
                break;
            case HANGAR:
                glBindTexture(GL_TEXTURE_2D, texturaHangar);
                break;
            case CUARTO_SECRETO:
                glBindTexture(GL_TEXTURE_2D, texturaCuartoSecreto);
                break;
            case SALA_DEL_JEFE:
                glBindTexture(GL_TEXTURE_2D, texturaSalaJefe);
                break;
            default:
                continue;
            }

            // Dibuja el bloque según la textura asignada
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 1.0f, z);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 1.0f, z);
            glEnd();
        }
    }
    glDisable(GL_TEXTURE_2D);
}*/