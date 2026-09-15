#include "tablero.h"
#include <cstdlib>
using namespace std;

unsigned char* generarTablero(int filas, int columnas,
                              int& bytes, int& sobrantes) {

    int cantidadFichas = filas * columnas;
    int bits = cantidadFichas * 3;

    bytes = (bits + 7) / 8;
    sobrantes = bytes * 8 - bits;

    unsigned char* memoria = new unsigned char[bytes]{};

    int byte = 0;
    int bit = 7 - sobrantes;

    for (int i = 0; i < cantidadFichas; i++) {

        unsigned char ficha = rand() % 6;

        if (bit >= 2) {
            // La ficha cabe en el byte actual.
            memoria[byte] |= ficha << (bit - 2);
        }
        else {
            // La ficha ocupa parte de dos bytes.
            memoria[byte] |= ficha >> (2 - bit);
            memoria[byte + 1] |= ficha << (6 + bit);
        }

        bit -= 3;

        if (bit < 0) {
            bit += 8;
            byte++;
        }
    }

    return memoria;
}
