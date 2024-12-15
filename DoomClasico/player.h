#ifndef PLAYER_H
#define PLAYER_H

extern float jugadorX;
extern float jugadorZ;
extern int mouseXAnterior;
extern int mouseYAnterior;

void inicializarJugador();
void manejarMovimientoJugador(unsigned char key);
void manejarMovimientoMouse(int x, int y);
void actualizarCamara();
//void dibujarArma();
void manejarDisparo(int button, int state, int x, int y);
//void cargarTexturasArmas();

#endif