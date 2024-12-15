#ifndef ENEMIGOS_H
#define ENEMIGOS_H

extern float enemigoX; // Coordenada X del enemigo
extern float enemigoZ; // Coordenada Z del enemigo

// Funciones relacionadas con el enemigo
void cargarSpriteEnemigo(); // Carga la textura del sprite
void dibujarEnemigo();      // Renderiza al enemigo
void  actualizarSprite();
void moverEnemigo();        // Actualiza la posición del enemigo


#endif // !ENEMIGOS_H
#pragma once