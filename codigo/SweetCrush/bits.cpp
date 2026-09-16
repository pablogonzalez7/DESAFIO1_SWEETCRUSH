#include "bits.h"

unsigned char leerFicha(unsigned char* puntero, int bit) {

    // Los tres bits caben en el mismo byte.
    if (bit >= 2) {
        return (*puntero >> (bit - 2)) & 7;
    }

    // La ficha está repartida entre dos bytes.
    unsigned int dosBytes = *puntero;
    dosBytes = (dosBytes << 8) | *(puntero + 1);

    return (dosBytes >> (bit + 6)) & 7;
}

void avanzarBits(unsigned char*& puntero, int& bit, int cantidad) {

    int posicion = (7 - bit) + cantidad;

    puntero += posicion / 8;
    bit = 7 - posicion % 8;
}
