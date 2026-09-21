#include "tablero.h"
#include "bits.h"
#include <cstdlib>
using namespace std;

void calcularMem(int filas, int columnas, int& bytesReservados, int& sobrantes) {

    int bits = filas * columnas * 3;

    bytesReservados = (bits + 7) / 8;
    sobrantes = bytesReservados * 8 - bits;
}

void calcularSobrantes(int bytesReservados, int filas, int columnas, int &sobrantes){
    int bits = filas * columnas * 3;
    int bitsReservados = bytesReservados*8;
    sobrantes = bitsReservados-bits;
}

unsigned char* generarTablero(int filas, int columnas,int& bytesReservados, int& sobrantes) {

    int cantidadFichas = filas * columnas;

    unsigned char* memoria = new unsigned char[bytesReservados]{};

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

bool verificarRedimensionarFilas(int columnas, int bytesReservados, int sobrantes){
    int bitsActivos= bytesReservados*8 - sobrantes;
    int newBits=columnas*3;
    return (bitsActivos+newBits>bytesReservados*8);
}

bool verificarRedimensionarColumnas(int filas, int bytesReservados, int sobrantes){
    int bitsActivos= bytesReservados*8 - sobrantes;
    int newBits = filas*3;
    return (bitsActivos+newBits>bytesReservados*8);
}

bool reducirmemoria(int filas, int columnas, int bytesReservados){
    return(filas*columnas*3<(bytesReservados*8*0.65));

}

void redimensionar(unsigned char* &tablero, int filas, int columnas, int& bytesReservados, int& sobrantes, int bytesNuevaReserva, int sobrantesNuevos){

    unsigned char* nuevoTablero= new unsigned char[bytesNuevaReserva]{};
    for(int c=0; c<filas*columnas; c++){
        unsigned char ficha= leerFicha(tablero,c,sobrantes);
        escribirFicha(nuevoTablero,c,sobrantesNuevos,ficha);
    }
    delete[] tablero;
    tablero = nuevoTablero;
    bytesReservados=bytesNuevaReserva;
    sobrantes=sobrantesNuevos;
}

void marcarFicha(unsigned char* auxiliar,int indice, int sobrantesAux){

    int posicionBit = indice + sobrantesAux;
    int byte = posicionBit / 8;
    int bit = 7 - posicionBit % 8;

    auxiliar[byte] &= ~(1 << bit);
}

unsigned char fichaMarcada(unsigned char* auxiliar,int indice,int sobrantesAux){

    int posicionBit = indice + sobrantesAux;
    int byte = posicionBit / 8;
    int bit = 7 - posicionBit % 8;

    return (auxiliar[byte] >> bit) & 1;
}
