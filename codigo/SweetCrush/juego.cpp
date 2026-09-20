#include "juego.h"
#include "bits.h"
#include <cstdlib>
#include<iostream>
using namespace std;

int leerEntero(const char mensaje[]) {
    char input[20];
    int valido;
    int numero;

    while (true) {
        cout << mensaje;
        cin >> input;
        valido = 1;

        int i = 0;
        while (input[i] != '\0') {
            if (input[i] < '0' || input[i] > '9'){
                valido = 0;
            }
            i++;
        }

        if (valido == 1) {
            numero = 0;
            int j = 0;
            while (input[j] != '\0') {
                numero = numero * 10 + (input[j] - '0');
                j++;
            }
            return numero;
        }

        cout << "Entrada invalida. Ingrese un numero entero."<<endl<<endl;
    }
}
void eliminarFicha(unsigned char* memoria, int filas, int columnas, int filaEliminar, int columnaEliminar, int sobrantes) {

    if (filaEliminar < 0 || filaEliminar >= filas ||
        columnaEliminar < 0 || columnaEliminar >= columnas) {
        return;
    }

    for (int fila = filaEliminar; fila > 0; fila--) {
        int destino = fila * columnas + columnaEliminar;
        int origen = destino - columnas;
        unsigned char ficha =leerFicha(memoria, origen, sobrantes);
        escribirFicha(memoria, destino, sobrantes, ficha);
    }

    unsigned char nuevaFicha = rand() % 6;
    escribirFicha(memoria, columnaEliminar, sobrantes, nuevaFicha);
}

void eliminarColumna(unsigned char* puntero,int filas, int &columnas, int columnaEliminar, int sobrantes){
    int c=1;
    int desplazamientos=1;
    for(int f = ((filas-1)*columnas) + columnaEliminar-2; f >= 0; f--){
        if(c%columnas==0){
            c++;
            desplazamientos++;
        }
        else{
            unsigned char Ficha = leerFicha(puntero,f,sobrantes);
            escribirFicha(puntero, f+desplazamientos, sobrantes, Ficha);
            c++;
        }

    } columnas--;
}

void eliminarFila(unsigned char* puntero, int &filas, int columnas, int filaEliminar, int sobrantes){

    for(int f=((filaEliminar-1)*columnas)-1; f>=0; f--){
        unsigned char ficha = leerFicha(puntero,f,sobrantes);
        escribirFicha(puntero, f+columnas, sobrantes, ficha);
    }filas--;
}

void agregarColumna(unsigned char* puntero,int filas, int &columnas, int columnaAgregar, int sobrantes){
    int c=1;
    int desplazamientos=filas;

    for(int f =(filas*columnas)-1;f>=columnaAgregar; f--){
        unsigned char Ficha = leerFicha(puntero,f,sobrantes);
        if (f==((filas-1)*columnas) +(columnaAgregar-1)){c=1; desplazamientos--;}
        escribirFicha(puntero, f+desplazamientos, sobrantes, Ficha);
        if(c%columnas==0){
            desplazamientos--;}
        c++;
    }columnas++;

    for(int n=0; n<filas;n++){
        int ind=(n*columnas)+columnaAgregar;
        unsigned char ficha= rand() % 6;
        escribirFicha(puntero,ind,sobrantes,ficha);
    }

}

void agregarFila(unsigned char* puntero,int &filas, int columnas, int filaAgregar, int sobrantes){
    for(int f=(filas*columnas)-1; f>= filaAgregar*columnas; f--){
        unsigned char ficha=leerFicha(puntero, f, sobrantes);
        escribirFicha(puntero,f+columnas,sobrantes, ficha);
    }filas++;
    for(int c=0; c<columnas; c++){
        int ind = (filaAgregar*columnas)+c;
        unsigned char ficha = rand() % 6;
        escribirFicha(puntero, ind, sobrantes, ficha);
    }

}
