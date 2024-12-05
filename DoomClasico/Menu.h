#ifndef MENU_H
#define MENU_H

#include <string>

// Estados del juego
enum GameState {
    MENU,
    GAME,
    INSTRUCTIONS
};

// Funciones para inicializar y dibujar el menú
void inicializarMenu();
void dibujarMenu();
void manejarMouseMenu(int boton, int estado, int x, int y);

// Funciones para el menú de instrucciones
void dibujarInstrucciones();

// Funciones auxiliares
void dibujarTextoCentrado(float x, float y, const std::string& texto, void* fuente, float escala);
void dibujarBoton(const struct Boton& boton);

#endif // MENU_H