#ifndef JUEGO_H
#define JUEGO_H

int leerEntero(const char mensaje[]);

void eliminarFicha(unsigned char* memoria, int filas, int columnas, int filaEliminar, int columnaEliminar, int sobrantes);

void eliminarColumna(unsigned char* puntero,int filas, int &columnas, int eliminarCol, int sobrantes);

void eliminarFila(unsigned char* puntero, int &filas, int columnas, int filaEliminar, int sobrantes);

void agregarColumna(unsigned char* puntero,int filas, int &columnas, int columnaAgregar, int sobrantes);

#endif
