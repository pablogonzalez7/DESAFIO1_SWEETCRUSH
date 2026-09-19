#include "bits.h"

int byteficha(int indice,int sobrantes){
    int posicionBit = indice * 3 + sobrantes;
    return(posicionBit / 8);
}

int bitficha(int indice, int sobrantes){
    int posicionBit = indice * 3 + sobrantes;
    return(7 - posicionBit % 8);
}

unsigned char leerFicha(unsigned char* puntero, int posicionLineal, int sobrantes) {


    int byte = byteficha(posicionLineal, sobrantes);
    int bit = bitficha( posicionLineal,sobrantes);

    if (bit >= 2) {
        return (puntero[byte] >> (bit - 2)) & 7;
    }

    unsigned char ficha;

    if (bit == 1) {
        ficha = (puntero[byte] & 3) << 1;
        ficha |= puntero[byte + 1] >> 7;
    }
    else {
        ficha = (puntero[byte] & 1) << 2;
        ficha |= puntero[byte + 1] >> 6;
    }

    return ficha;
}

void escribirFicha(unsigned char* puntero, int posicionLineal, int sobrantes, unsigned char ficha) {

    int posicionBit = posicionLineal * 3 + sobrantes;

    int byte = posicionBit / 8;
    int bit = 7 - posicionBit % 8;

    if (bit >= 2) {
        puntero[byte] &= ~(7 << (bit - 2));
        puntero[byte] |= ficha << (bit - 2);
    }
    else if (bit == 1) {
        // Dos bits en este byte y uno en el siguiente.
        puntero[byte] &= ~3;
        puntero[byte] |= ficha >> 1;

        puntero[byte + 1] &= ~(1 << 7);
        puntero[byte + 1] |= (ficha & 1) << 7;
    }
    else {
        // Un bit en este byte y dos en el siguiente.
        puntero[byte] &= ~1;
        puntero[byte] |= ficha >> 2;

        puntero[byte + 1] &= ~(3 << 6);
        puntero[byte + 1] |= (ficha & 3) << 6;
    }
}
