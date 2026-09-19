#include "interfaz.h"
#include "bits.h"
#include <iostream>
using namespace std;

void imprimirTablero(unsigned char* memoria, int filas, int columnas, int sobrantes) {

    int posicionLineal = 0;

    for (int fila = 0; fila < filas; fila++) {

        for (int columna = 0; columna < columnas; columna++) {

            unsigned char ficha =
                leerFicha(memoria, posicionLineal, sobrantes);

            switch (ficha) {
            case 0: cout << "$|"; break;
            case 1: cout << "O|"; break;
            case 2: cout << "X|"; break;
            case 3: cout << "?|"; break;
            case 4: cout << "#|"; break;
            case 5: cout << "@|"; break;
            }

            posicionLineal++;
        }

        cout << '\n';
    }
}
