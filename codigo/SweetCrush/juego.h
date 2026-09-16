#ifndef JUEGO_H
#define JUEGO_H

bool marcarFicha(unsigned char* marcas, int posicion);

int detectarCombinaciones(unsigned char* memoria,
                          unsigned char* marcas,
                          int filas, int columnas, int sobrantes);

#endif
