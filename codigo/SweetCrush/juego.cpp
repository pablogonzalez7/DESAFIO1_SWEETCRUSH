#include "juego.h"
#include "bits.h"
#include <cstdlib>

void eliminarFicha(unsigned char* memoria, int filas, int columnas, int filaEliminar, int columnaEliminar, int sobrantes) {

    if (filaEliminar < 0 || filaEliminar >= filas ||
        columnaEliminar < 0 || columnaEliminar >= columnas) {
        return;
    }

    // Bajar una posición cada ficha situada encima.
    for (int fila = filaEliminar; fila > 0; fila--) {

        int destino = fila * columnas + columnaEliminar;
        int origen = destino - columnas;

        unsigned char ficha =
            leerFicha(memoria, origen, sobrantes);

        escribirFicha(memoria, destino, sobrantes, ficha);
    }

    // En la fila 0, el índice lineal coincide con la columna.
    unsigned char nuevaFicha = rand() % 6;

    escribirFicha(memoria, columnaEliminar,
                  sobrantes, nuevaFicha);
}
