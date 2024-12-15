#include "vida.h"
#include <GL/glut.h>
#include <iostream>

Vida::Vida(int maxHealth) : maxHealth(maxHealth), currentHealth(maxHealth) {
    //std::cout << "Inicializando Vida: maxHealth = " << maxHealth << ", currentHealth = " << currentHealth << std::endl; // Depuración
}

Vida::~Vida() {

}

void Vida::render() {
    //std::cout << "Renderizando barra de vida. Salud actual: " << currentHealth << " de " << maxHealth << std::endl;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    float healthRatio = static_cast<float>(currentHealth) / maxHealth;
    //std::cout << "Proporción de Salud: " << healthRatio << std::endl;
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(10, 570);
    glVertex2f(10 + 200.0f * healthRatio, 570);
    glVertex2f(10 + 200.0f * healthRatio, 590);
    glVertex2f(10, 590);
    glEnd();

    glColor3f(0.0f, 0.39f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(10 + 200.0f * healthRatio, 570);
    glVertex2f(210, 570);
    glVertex2f(210, 590);
    glVertex2f(10 + 200.0f * healthRatio, 590);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Vida::setHealth(int health) {
    currentHealth = (health > maxHealth) ? maxHealth : (health < 0) ? 0 : health;
    //std::cout << "Salud actualizada: " << currentHealth << " de " << maxHealth << std::endl;
}

int Vida::getHealth() const {
    return currentHealth;
}

