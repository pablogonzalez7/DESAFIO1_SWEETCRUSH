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
    int bytesNuevaReserva=0;
    int sobrantes = 0;
    int sobrantesNuevos=0;
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

    calcularMem(filas, columnas, bytesReservados, sobrantes);

    unsigned char* tablero = generarTablero(filas,columnas,bytesReservados,sobrantes);

    cout<<endl;
    imprimirTablero(tablero, filas, columnas, sobrantes);

    while(continuar){

    cout<<endl<<"1. Eliminar ficha"<<endl
         <<"2. Agregar fila"<<endl
         <<"3. Eliminar fila"<<endl
         <<"4. Agregar columna"<<endl
         <<"5. Eliminar columna"<<endl
         <<"6. Salir"<<endl;
        accion=leerEntero("ingresa accion(1-6): ");
    cout<<endl;

    switch (accion) {


    case 1:

        int fila, columna;
        cout<<"Los indices de filas y columnas van de 1 a la cantidad"<<endl
             <<"Fila: ";
        cin>>fila;
        cout<<"columna: ";
        cin>>columna;

        eliminarFicha(tablero, filas, columnas, fila-1, columna-1, sobrantes);

        cout<<endl;
        imprimirTablero(tablero, filas, columnas, sobrantes);
        cout<<endl;
        break;


    case 2:

        if(verificarRedimensionarFilas(columnas, bytesReservados, sobrantes)){
            calcularMem(filas+1, columnas, bytesNuevaReserva, sobrantesNuevos);
            redimensionar(tablero, filas, columnas, bytesReservados, sobrantes, bytesNuevaReserva, sobrantesNuevos);
        }
        int filaAgregar;
        do {
            filaAgregar = leerEntero("Ingrese posicion de la nueva fila: ");

            if (filaAgregar < 1 || filaAgregar > filas+1) {
                cout << "Fila invalida. Debe estar entre 1 y " << filas+1 << endl;
            }

        } while (filaAgregar < 1 || filaAgregar > filas+1);
        agregarFila(tablero,filas, columnas, filaAgregar-1, sobrantes);
        cout<<endl;
        imprimirTablero(tablero, filas, columnas, sobrantes);

        break;


    case 3:
        if(columnas==0 || filas==0){cout<<"No hay filas para eliminar"<<endl; break;}
        int filaEliminar;
        do {
            filaEliminar = leerEntero("Ingrese numero de fila a eliminar: ");

            if (filaEliminar < 1 || filaEliminar > filas) {
                cout << "Fila invalida. Debe estar entre 1 y " << filas << endl;
            }

        } while (filaEliminar < 1 || filaEliminar > filas);
        eliminarFila(tablero , filas, columnas, filaEliminar, sobrantes);
        calcularSobrantes(bytesReservados, filas, columnas, sobrantes);
        if(reducirmemoria( filas, columnas, bytesReservados)){
            calcularMem(filas, columnas, bytesReservados, sobrantesNuevos);
            redimensionar(tablero, filas, columnas, bytesReservados, sobrantes, bytesNuevaReserva, sobrantesNuevos);

        }
        cout<<endl;
        imprimirTablero(tablero, filas, columnas, sobrantes);
        break;


    case 4:

        if(verificarRedimensionarColumnas(filas, bytesReservados, sobrantes)){
            calcularMem(filas, columnas+1, bytesNuevaReserva, sobrantesNuevos);
            redimensionar(tablero, filas, columnas, bytesReservados, sobrantes, bytesNuevaReserva, sobrantesNuevos);
            }
        int columnaAgregar;
            do {
                columnaAgregar = leerEntero("Ingrese posicion de la nueva columna: ");

                if (columnaAgregar < 1 || columnaAgregar > columnas+1) {
                    cout << "columna invalida. Debe estar entre 1 y " << columnas+1 << endl;
                }

            } while (columnaAgregar < 1 || columnaAgregar > columnas+1);
        agregarColumna(tablero,filas, columnas, columnaAgregar-1, sobrantes);
        cout<<endl;
        imprimirTablero(tablero, filas, columnas, sobrantes);

        break;


    case 5:

        if(columnas==0 || filas==0){cout<<"No hay columnas para eliminar"<<endl; break;}
            int columnaEliminar;
            do {
                columnaEliminar = leerEntero("Ingrese numero de columna a eliminar: ");

                if (columnaEliminar < 1 || columnaEliminar > columnas) {
                    cout << "Columna invalida. Debe estar entre 1 y " << columnas << endl;
                }

            } while (columnaEliminar < 1 || columnaEliminar > columnas);
            eliminarColumna(tablero, filas, columnas, columnaEliminar, sobrantes);
            calcularSobrantes(bytesReservados, filas, columnas, sobrantes);
            if(reducirmemoria(filas, columnas, bytesReservados)){
                calcularMem(filas, columnas, bytesReservados, sobrantesNuevos);
                redimensionar(tablero, filas, columnas, bytesReservados, sobrantes, bytesNuevaReserva, sobrantesNuevos);
            }
            cout<<endl;
            imprimirTablero(tablero, filas, columnas, sobrantes);
            break;

    case 6:

        continuar=false;

        break;

    default:
        cout<<"Invalido. Ingrese de 1 a 6: "<<endl;
    }


    }

    return 0;
}
