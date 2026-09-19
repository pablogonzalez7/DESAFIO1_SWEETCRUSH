#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tablero.h"
#include "interfaz.h"
#include "juego.h"

using namespace std;

int main() {

    bool continuar=true;

    int filas = 0;
    int columnas = 0;
    int bytesReservados = 0;
    int sobrantes = 0;
    int accion;

    cout << "Ingrese la cantidad de filas: ";
    cin >> filas;

    cout << "Ingrese la cantidad de columnas: ";
    cin >> columnas;

    if (filas <= 0 || columnas <= 0) {
        cout << "Dimensiones invalidas.\n";
        return 1;
    }

    srand(time(0));

    unsigned char* tablero = generarTablero(filas,columnas,bytesReservados,sobrantes);

    imprimirTablero(tablero, filas, columnas, sobrantes);

    while(continuar){

    cout<<"1. Eliminar ficha"<<endl
         <<"2. Eliminar fila"<<endl
         <<"3. Agregar fila"<<endl
         <<"4. Eliminar columna"<<endl
         <<"5. Agregar columna"<<endl;
    cin>>accion;

    switch (accion) {
    case 1:

        int fila, columna;
        cout<<"Los indices de filas y columnas inician desde cero"<<endl
             <<"Fila: "<<endl;
        cin>>fila;
        cout<<"columna: "<<endl ;
        cin>>columna;

        eliminarFicha(tablero, filas, columnas, fila, columna, sobrantes);

        imprimirTablero(tablero, filas, columnas, sobrantes);


        break;
    default:
        break;
    }

    char s;
    cout<<"ingrese S si desea salir: ";
    cin>>s;
    if ((s == 's' || s == 'S')) {
        continuar=false;
    }

    }

    return 0;
}
