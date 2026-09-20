#ifndef TABLERO_H
#define TABLERO_H

void calcularMem(int filas, int columnas, int& bytesNecesarios, int& sobrantes);

void calcularSobrantes(int bitsReservados, int filas, int columnas, int &sobrantes);

unsigned char* generarTablero(int filas, int columnas,int& bytesReservados, int& sobrantes);

bool verificarRedimensionarFilas(int columnas, int bytesReservados, int sobrantes);

bool verificarRedimensionarColumnas(int filas, int bytesReservados, int sobrantes);

bool reducirmemoria(int filas, int columnas, int bytesReservados);

void redimensionar(unsigned char* &tablero, int filas, int columnas, int& bytesReservados, int& sobrantes, int bytesNuevaReserva, int sobrantesNuevos);

#endif
