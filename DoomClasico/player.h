#ifndef PLAYER_H
#define PLAYER_H

extern int mouseXAnterior;
extern int mouseYAnterior;

void inicializarJugador();
void manejarMovimientoJugador(unsigned char key);
void manejarMovimientoMouse(int x, int y);
void actualizarCamara();

#endif