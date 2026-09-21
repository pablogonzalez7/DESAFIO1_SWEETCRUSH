#include "interfaz.h"
#include "bits.h"
#include "juego.h"
#include <iostream>
using namespace std;

void imprimirTablero(unsigned char* memoria, int filas, int columnas, int sobrantes){

    int posicionLineal = 0;

    for(int c=0; c<columnas; c++){
        cout << "+---";
    }
    cout << "+\n";

    for(int fila=0; fila<filas; fila++){

        for(int columna=0; columna<columnas; columna++){

            unsigned char ficha = leerFicha(memoria, posicionLineal, sobrantes);

            cout << "| ";

            switch(ficha){
            case 0: cout << "$"; break;
            case 1: cout << "O"; break;
            case 2: cout << "X"; break;
            case 3: cout << "?"; break;
            case 4: cout << "#"; break;
            case 5: cout << "@"; break;
            }

            cout << " ";
            posicionLineal++;
        }

        cout << "|\n";

        for(int c=0; c<columnas; c++){
            cout << "+---";
        }
        cout << "+\n";
    }
}

void imprimirTableroBits(unsigned char* memoria, int filas, int columnas, int sobrantes){

    int posicionLineal = 0;

    for(int c=0; c<columnas; c++){
        cout << "+---";
    }
    cout << "+\n";

    for(int fila=0; fila<filas; fila++){

        for(int columna=0; columna<columnas; columna++){

            unsigned char ficha = leerFicha(memoria, posicionLineal, sobrantes);

            cout << "|";
            cout << ((ficha >> 2) & 1);
            cout << ((ficha >> 1) & 1);
            cout << (ficha & 1);

            posicionLineal++;
        }

        cout << "|\n";

        for(int c=0; c<columnas; c++){
            cout << "+---";
        }
        cout << "+\n";
    }
}

void imprimirTableros(unsigned char* memoria, int filas, int columnas, int sobrantes){
    imprimirTableroBits(memoria, filas, columnas, sobrantes);
    cout<<filas<<"x"<<columnas<<endl,
    imprimirTablero(memoria,filas,columnas, sobrantes);
}

void tablerosYestado(unsigned char* tablero, int filas, int columnas, int sobrantes, int& fichasEliminadas, int& combinacionesDetectadas, int& cascadasActuales, int eliminacionesUsuario){

    resolverCascadas(tablero, filas, columnas, sobrantes, fichasEliminadas, combinacionesDetectadas, cascadasActuales);

    imprimirTableros(tablero, filas, columnas, sobrantes);

    cout << "FICHAS ELIMINADAS: "<< eliminacionesUsuario + fichasEliminadas << endl;
    cout << "ELIMINADAS POR EL USUARIO: "<< eliminacionesUsuario << endl;
    cout << "ELIMINADAS EN COMBINACIONES: "<< fichasEliminadas << endl;
    cout << "COMBINACIONES DETECTADAS: "<< combinacionesDetectadas << endl;
    cout << "CASCADAS: "<< cascadasActuales << endl;
    mostrarPuntuacion(fichasEliminadas, combinacionesDetectadas);
    cout<<endl;
}

