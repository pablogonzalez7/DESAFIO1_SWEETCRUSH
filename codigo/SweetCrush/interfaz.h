#ifndef INTERFAZ_H
#define INTERFAZ_H

void imprimirTablero(unsigned char* memoria, int filas, int columnas, int sobrantes);
void imprimirTableroBits(unsigned char* memoria, int filas, int columnas, int sobrantes);
void imprimirTableros(unsigned char* memoria, int filas, int columnas, int sobrantes);
void tablerosYestado(unsigned char* tablero, int filas, int columnas, int sobrantes, int& fichasEliminadas, int& combinacionesDetectadas, int& cascadasActuales, int eliminacionesUsuario);

#endif
