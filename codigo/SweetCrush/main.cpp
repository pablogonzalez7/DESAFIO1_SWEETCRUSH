#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tablero.h"
#include "interfaz.h"

using namespace std;

int main() {

    int filas = 0;
    int columnas = 0;
    int bytes = 0;
    int sobrantes = 0;

    cout << "Ingrese la cantidad de filas: ";
    cin >> filas;

    cout << "Ingrese la cantidad de columnas: ";
    cin >> columnas;

    if (filas <= 0 || columnas <= 0) {
        cout << "Dimensiones invalidas.\n";
        return 1;
    }

    srand(time(0));

    // Esta llamada reserva la memoria y genera las fichas.
    unsigned char* tablero =
        generarTablero(filas, columnas, bytes, sobrantes);

    cout << "\nTablero inicial:\n";
    imprimirTablero(tablero, filas, columnas, sobrantes);

    // Liberar la reserva al terminar.
    delete[] tablero;

    return 0;
}
