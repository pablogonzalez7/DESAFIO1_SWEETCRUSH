#ifndef TABLERO_H
#define TABLERO_H

void calcularMem(int filas, int columnas, int& bytesNecesarios, int& sobrantes);

unsigned char* generarTablero(int filas, int columnas,int& bytesReservados, int& sobrantes);

#endif
