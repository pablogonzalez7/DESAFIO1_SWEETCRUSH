#ifndef JUEGO_H
#define JUEGO_H

int leerEntero(const char mensaje[]);

void eliminarFicha(unsigned char* memoria, int filas, int columnas, int filaEliminar, int columnaEliminar, int sobrantes);

void eliminarColumna(unsigned char* puntero,int filas, int &columnas, int eliminarCol, int sobrantes);

void eliminarFila(unsigned char* puntero, int &filas, int columnas, int filaEliminar, int sobrantes);

void agregarColumna(unsigned char* puntero,int filas, int &columnas, int columnaAgregar, int sobrantes);

void agregarFila(unsigned char* puntero,int &filas, int columnas, int filaAgregar, int sobrantes);

void detectarCombinaciones(unsigned char* tablero, int filas, int columnas, int sobrantes, int& fichasEliminada, int& combinacionesDetectadas);

void realizarCaidas(unsigned char* tablero,int filas,int columnas,int sobrantes,unsigned char* auxiliar,int sobrantesAuxiliar, int& fichasEliminadas);

void resolverCascadas(unsigned char* tablero,int filas,int columnas,int sobrantes,int& fichasEliminadas,int& combinacionesDetectadas,int& cascadasActuales);

void mostrarPuntuacion(int fichasEliminadas, int combinacionesDetectadas);

#endif
