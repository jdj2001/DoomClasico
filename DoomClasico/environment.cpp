#include <GL/glew.h>
#include <GL/glut.h>
#include "textures.h"
#include "environment.h"
#include <string>
#include "enemies.h"
#include <cmath>

const int MAP_SIZE = 30;

const std::string MAP[MAP_SIZE][MAP_SIZE] = { 
    {"P2", "P2", "P2", "P2", "P2", "P2", "P2", "P2", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P3", "P3", "P3", "P3", "P3", "P3", "P3", "P3", "P3", "P3"},
    {"P2", "S2", "S2", "S2", "S2", "S2", "S2", "S2", "P", "S", "S", "S", "S", "P", "S", "S", "S", "P3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "P3"},
    {"P2", "S2", "S2", "S2", "S2", "S2", "S2", "S2", "P", "S", "S", "S", "S", "D", "S", "S", "S", "P3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "P3"},
    {"P2", "S2", "S2", "S2", "S2", "S2", "S2", "S2", "D", "S", "S", "S", "S", "P", "S", "S", "S", "P3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "P3"},
    {"P2", "S2", "S2", "S2", "S2", "S2", "S2", "S2", "D", "S", "S", "S", "S", "P", "S", "S", "S", "D2", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "P3"},
    {"P2", "S2", "S2", "S2", "S2", "S2", "S2", "S2", "D", "S", "S", "S", "S", "P", "S", "S", "S", "D2", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "P3"},
    {"P2", "S2", "S2", "S2", "S2", "S2", "S2", "S2", "P", "S", "S", "S", "S", "D", "S", "S", "S", "D2", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "P3"},
    {"P2", "P2", "P2", "P2", "P2", "P2", "P2", "P2", "P", "S", "S", "S", "S", "P", "S", "S", "S", "P3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "P3"},
    {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "P", "S", "S", "S", "S", "P", "S", "S", "S", "P3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "S3", "P3"},
    {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "P", "P", "P", "P", "P", "P", "P", "P", "P", "P3", "P3", "P3", "P3", "P3", "P3", "P3", "D3", "D3", "P3", "P3"},
    {"P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P4", "P4", "P4", "S4", "S4", "P4", "P4"},
    {"P5", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "P5", "S4", "S4", "S4", "S4", "S4", "S4", "P4"},
    {"P5", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "P5", "S4", "S4", "S4", "S4", "S4", "S4", "P4"},
    {"P5", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "P5", "S4", "S4", "S4", "S4", "S4", "S4", "P4"},
    {"P5", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "D4", "S4", "S4", "S4", "S4", "S4", "S4", "P4"},
    {"P5", "S8", "S8", "S8", "S8", "S8", "S8", "S8", "S8", "S8", "O", "O", "S5", "S5", "S5", "S5", "S5", "S5", "S5", "S5", "D4", "S4", "S4", "S4", "S4", "S4", "S4", "P4"},
    {"P5", "S8", "S8", "S8", "S8", "S8", "S8", "S8", "S8", "S8", "O", "O", "S5", "S5", "S5", "S5", "S5", "S5", "S5", "S5", "D4", "S4", "S4", "S4", "S4", "S4", "S4", "P4"},
    {"P5", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "S6", "D4", "S4", "S4", "S4", "S4", "S4", "S4", "P4"},
    {"P5", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "P5", "S4", "S4", "S4", "S4", "S4", "S4", "P4"},
    {"P5", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "P5", "S4", "S4", "S4", "S4", "S4", "S4", "P4"},
    {"P5", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "S7", "P5", "S4", "S4", "S4", "S4", "S4", "S4", "P4"},
    {"P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P5", "P4", "P4", "P4", "P4", "P4", "P4", "P4"}
};

void inicializarEntorno() {
    loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/tn116.jpg");
    loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/paredes/tn373.jpg");
}

void dibujarMapa() {
    glEnable(GL_TEXTURE_2D);

    const int techo = 5;
    const int ArmaEspecial = 2;

    //AREA INICIAL
    GLuint texturaTechoInicio = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/techo/techo_bloque_2.png");
    GLuint texturaParedInicio = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/paredes/pared2_bloque.png");
    GLuint texturaSueloInicio = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/104_naranja_oscuro.png");

    //AREA ENEMIGOS 1
    GLuint texturaSueloArea1 = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/suelo_area_1.png");
    GLuint texturaParedArea1 = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/paredes/pared_area_1.png");
    GLuint texturaTechoArea1 = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/techo/techo_area_1.png");

    //AREA ENEMIGOS 2
    GLuint texturaTechoArea2 = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/techo/techo_bloque_2.png");
    GLuint texturaParedArea2 = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/paredes/pared_area_2.png");
    GLuint texturaSueloArea2 = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/suelo_area_2.png");

    //AREA POWERUPS
    GLuint texturaTechoArea3 = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/techo/techo_area_3.png");
    GLuint texturaParedArea3_1 = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/paredes/pared_area_3_1.png");
    GLuint texturaParedArea3_2 = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/paredes/pared_area_3_2.png");
    GLuint texturaSueloArea3 = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/suelo_area_3.png");

    //AREA JEFE
    //suelo central
    GLuint texturaSueloArea4_central = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/sueloCentral_area_jefe.png");//S5 y S8
    //suelo central lateral
    GLuint texturaSueloArea4_centralLateral = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/sueloCentralLateral_area_jefe.png");//S6
    //suelo lateral
    GLuint texturaSueloArea4_Lateral = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/sueloLateral_area_jefe.png");//S7

    //pared normal
    GLuint texturaParedArea4 = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/paredes/paredNormal_area_jefe2.png");//ajustar en todo menos posiciones x espec�ficas
    //pared central
    GLuint texturaParedArea4_central = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/paredes/paredCentral_area_jefe.png");//ajustar en x

    //techo
    GLuint texturaTechoArea4_centralInicial = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/techo/techoCentralInicial_jefe.png");//con suelo S5
    GLuint texturaTechoArea4_CentralFinal = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/techo/techoCentralFinal_jefe.png");//con suelo S8
    GLuint texturaTechoArea4_Lateral = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/techo/techoCentralLateral_jefe.png");//con suelo S6 y S7

    //ARMA ESPECIAL
    GLuint texturaPlataformaArea_ArmaEspecial = loadTexture("D:/clases/Comp Grafica y Visual/III/DoomClasico/DoomClasico/DoomClasico/sprites/suelo/sueloArmaEspecial3.png");
    
    for (int x = 0; x < MAP_SIZE; x++) {
        for (int z = 0; z < MAP_SIZE; z++) {
            for (int y = 0; y < techo; y++) {
                if (MAP[x][z] == "P") {
                    glBindTexture(GL_TEXTURE_2D, texturaParedArea1);
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
                else if (MAP[x][z] == "P2") {
                    glBindTexture(GL_TEXTURE_2D, texturaParedInicio);
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
                else if (MAP[x][z] == "P3") {
                    glBindTexture(GL_TEXTURE_2D, texturaParedArea2);
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
                else if (MAP[x][z] == "P4") {
                    glBindTexture(GL_TEXTURE_2D, texturaParedArea3_1);
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
                else if (MAP[x][z] == "P5") {
                    glBindTexture(GL_TEXTURE_2D, texturaParedArea4);
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
                    glBindTexture(GL_TEXTURE_2D, texturaParedArea1);
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
                glBindTexture(GL_TEXTURE_2D, texturaSueloArea1);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            else if (MAP[x][z] == "D2") {
                for (int y = 3; y < techo; y++) {
                    glBindTexture(GL_TEXTURE_2D, texturaParedArea2);
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
                glBindTexture(GL_TEXTURE_2D, texturaSueloArea2);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            else if (MAP[x][z] == "D3") {
                for (int y = 3; y < techo; y++) {
                    glBindTexture(GL_TEXTURE_2D, texturaParedArea3_1);
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
                glBindTexture(GL_TEXTURE_2D, texturaSueloArea3);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            else if (MAP[x][z] == "D4") {
                for (int y = 3; y < techo; y++) {
                    glBindTexture(GL_TEXTURE_2D, texturaParedArea4);
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
                glBindTexture(GL_TEXTURE_2D, texturaSueloArea4_Lateral);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            //AREA 1
            if (MAP[x][z] == "S") {
                glBindTexture(GL_TEXTURE_2D, texturaSueloArea1);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            if (MAP[x][z] == "S") {
                glBindTexture(GL_TEXTURE_2D, texturaTechoArea1);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, techo + 1.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, techo + 1.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, techo + 1.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, techo + 1.0f, z);

                
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, techo, z);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, techo, z);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, techo, z + 1.0f);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, techo, z + 1.0f);
                glEnd();
            }
            //AREA INICIAL
            if (MAP[x][z] == "S2") {
                glBindTexture(GL_TEXTURE_2D, texturaSueloInicio);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            if (MAP[x][z] == "S2") {
                glBindTexture(GL_TEXTURE_2D, texturaTechoInicio);
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
            //AREA 2
            if (MAP[x][z] == "S3") {
                glBindTexture(GL_TEXTURE_2D, texturaSueloArea2);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            if (MAP[x][z] == "S3") {
                glBindTexture(GL_TEXTURE_2D, texturaTechoArea2);
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
            //AREA 3
            if (MAP[x][z] == "S4") {
                glBindTexture(GL_TEXTURE_2D, texturaSueloArea3);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            if (MAP[x][z] == "S4") {
                glBindTexture(GL_TEXTURE_2D, texturaTechoArea3);
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
            //AREA 4 - parte 1
            if (MAP[x][z] == "S5") {
                glBindTexture(GL_TEXTURE_2D, texturaSueloArea4_central);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            if (MAP[x][z] == "S5") {
                glBindTexture(GL_TEXTURE_2D, texturaTechoArea4_centralInicial);
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
            //AREA 4 - parte 2
            if (MAP[x][z] == "S6") {
                glBindTexture(GL_TEXTURE_2D, texturaSueloArea4_centralLateral);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            if (MAP[x][z] == "S6") {
                glBindTexture(GL_TEXTURE_2D, texturaTechoArea4_Lateral);
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
            //AREA 4 - parte 3
            if (MAP[x][z] == "S7") {
                glBindTexture(GL_TEXTURE_2D, texturaSueloArea4_Lateral);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            if (MAP[x][z] == "S7") {
                glBindTexture(GL_TEXTURE_2D, texturaTechoArea4_Lateral);
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
            //AREA 4 - parte 4
            if (MAP[x][z] == "S8") {
                glBindTexture(GL_TEXTURE_2D, texturaSueloArea4_central);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glEnd();
            }
            if (MAP[x][z] == "S8") {
                glBindTexture(GL_TEXTURE_2D, texturaTechoArea4_CentralFinal);
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
            //ARMA ESPECIAL
            if (MAP[x][z] == "O") {
                glBindTexture(GL_TEXTURE_2D, texturaPlataformaArea_ArmaEspecial);
                glBegin(GL_QUADS);

                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 1.0f, z);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 1.0f, z);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z);

                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x, 1.0f, z + 1.0f);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 1.0f, z);

                glTexCoord2f(0.0f, 0.0f); glVertex3f(x + 1.0f, 1.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x, 1.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);

                glTexCoord2f(0.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 1.0f, z);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x + 1.0f, 1.0f, z + 1.0f);

                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, z);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 0.0f, z);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f, z + 1.0f);

                glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 1.0f, z + 1.0f);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 1.0f, 1.0f, z + 1.0f);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 1.0f, 1.0f, z);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 1.0f, z);

                glEnd();
            }

            if (MAP[x][z] == "O") {
                glBindTexture(GL_TEXTURE_2D, texturaTechoArea4_CentralFinal);
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
    dibujarEnemigos();
}

/*bool esCeldaBloqueada(const std::string& celda) {
    return celda == "P" || celda == "D" || celda == "P2";
}*/
bool esCeldaBloqueada(const std::string& celda) {
    return celda != "D" && celda != "D1" && celda != "D2" &&
        celda != "D3" && celda != "D4" &&
        (celda == "P" || celda == "P2" || celda == "P3" || celda == "P4" || celda == "P5" || celda == "O");
}

bool colisionConMapa(float jugadorX, float jugadorZ) {
    //MARGEN DE COLISI�N PARA QUE NO ATRAVIESE LAS PAREDES (NO FUNCIONA SIN LAS VERIFICACIONES POSTERIORES)
    const float margenColision = -0.2f; 

    int gridX = static_cast<int>(jugadorX);
    int gridZ = static_cast<int>(jugadorZ);

    //LIMITES DEL MAPA
    if (gridX < 0 || gridX >= MAP_SIZE || gridZ < 0 || gridZ >= MAP_SIZE) {
        return true;
    }

    //SI SE LLEGA A LAS PAREDES, SE COLISIONA CON LOS BLOQUES/CELDAS
    const std::string& celda = MAP[gridX][gridZ];
    if (esCeldaBloqueada(celda)) {
        float bordeIzquierdo = gridX + margenColision;
        float bordeDerecho = gridX + 1.0f - margenColision;
        float bordeSuperior = gridZ + margenColision;
        float bordeInferior = gridZ + 1.0f - margenColision;

        if (jugadorX >= bordeIzquierdo && jugadorX <= bordeDerecho &&
            jugadorZ >= bordeSuperior && jugadorZ <= bordeInferior) {
            return true;
        }
    }

    //AUN QUEDA MARGEN EN EL QUE EL JUGADOR PUEDE VER DENTRO DE LAS PAREDES, POR LO QUE
    //SE DEBE VERIFICAR LAS COLISIONES CON LAS CELDAS ADYACENTES PARA QUE EXISTAN COLISIONES CON LAS
    //DIAGONALES Y MEJORAR LA DETECCI�N DE COLISIONES
    for (int offsetX = -1; offsetX <= 1; ++offsetX) {
        for (int offsetZ = -1; offsetZ <= 1; ++offsetZ) {
            int vecinoX = gridX + offsetX;
            int vecinoZ = gridZ + offsetZ;

            //LO MISMO QUE EL LIMITE DEL MAPA AL INICIO, SOLO QUE PARA VERIFICAR LAS DIAGONALES (DEM�S CARAS DEL CUBO)
            if (vecinoX < 0 || vecinoX >= MAP_SIZE || vecinoZ < 0 || vecinoZ >= MAP_SIZE) {
                continue;
            }

            //DE NUEVO LA MISMA VERIFICACI�N DE CELDA AHORA PARA LAS DEM�S CARAS
            const std::string& celdaVecina = MAP[vecinoX][vecinoZ];
            if (esCeldaBloqueada(celdaVecina)) {
                float bordeIzquierdo = vecinoX + margenColision;
                float bordeDerecho = vecinoX + 1.0f - margenColision;
                float bordeSuperior = vecinoZ + margenColision;
                float bordeInferior = vecinoZ + 1.0f - margenColision;

                if (jugadorX >= bordeIzquierdo && jugadorX <= bordeDerecho &&
                    jugadorZ >= bordeSuperior && jugadorZ <= bordeInferior) {
                    return true;
                }
            }
        }
    }

    return false;
}