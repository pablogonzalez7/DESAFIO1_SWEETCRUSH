#include "interfaz.h"
#include "bits.h"
#include <iostream>
using namespace std;

void imprimirTablero(unsigned char* memoria, int filas,
                     int columnas, int sobrantes) {

    int byte = 0;
    int bit = 7 - sobrantes;

    for (int fila = 0; fila < filas; fila++) {

        for (int columna = 0; columna < columnas; columna++) {

            unsigned char ficha = leerFicha(&memoria[byte], bit);

            switch (ficha) {
            case 0: cout << "$ "; break;
            case 1: cout << "O "; break;
            case 2: cout << "X "; break;
            case 3: cout << "? "; break;
            case 4: cout << "# "; break;
            case 5: cout << "@ "; break;
            }

            bit -= 3;

            if (bit < 0) {
                bit += 8;
                byte++;
            }
        }

        cout << '\n';
    }
}
