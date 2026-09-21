#include "juego.h"
#include "bits.h"
#include "tablero.h"
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

void detectarCombinaciones(unsigned char* tablero, int filas, int columnas, int sobrantes, int& fichasEliminadas, int& combinacionesDetectadas){
    int fichas=filas*columnas;
    int bytesAuxiliar= (fichas+7)/8;
    int sobrantesAuxiliar= (bytesAuxiliar*8)-fichas;
    unsigned char* auxiliar= new unsigned char[bytesAuxiliar];
    for(int i=0; i<bytesAuxiliar; i++){
        auxiliar[i] = 255;
    }
    int fv;
    for(int f=0;f<filas;f++){
        unsigned char f1,f2,f3,actual=0,anterior=0;
        for(int c=0; c<columnas-2; c++){
            fv=f*columnas+c;
            f1=leerFicha(tablero,fv,sobrantes);
            f2=leerFicha(tablero,fv+1,sobrantes);
            f3=leerFicha(tablero,fv+2,sobrantes);
            if (f1==f2 && f2==f3){actual=1;}
            else{actual=0;}

            if (anterior==0 && actual==0) {
            }
            else if (anterior==1 && actual==0) {
                c++;
            }
            else if (anterior==1 && actual==1) {
                marcarFicha(auxiliar,fv+2,sobrantesAuxiliar);
            }
            else {
                marcarFicha(auxiliar,fv,sobrantesAuxiliar);

                marcarFicha(auxiliar,fv+1,sobrantesAuxiliar);

                marcarFicha(auxiliar,fv+2,sobrantesAuxiliar);

                combinacionesDetectadas++;
            }anterior=actual;
        }
    }

        for(int f=0;f<columnas;f++){
            unsigned char f1,f2,f3,actual=0,anterior=0;
            for(int c=0; c<filas-2; c++){
                fv=(c*columnas)+f;
                f1=leerFicha(tablero,fv,sobrantes);
                f2=leerFicha(tablero,fv+columnas,sobrantes);
                f3=leerFicha(tablero,fv+(2*columnas),sobrantes);
                if (f1==f2 && f2==f3){actual=1;}
                else{actual=0;}

                if (anterior==0 && actual==0) {
                }
                else if (anterior==1 && actual==0) {
                    c++;
                }
                else if (anterior==1 && actual==1) {
                    if(fichaMarcada(auxiliar,fv+(2*columnas),sobrantesAuxiliar)){
                        marcarFicha(auxiliar,fv+(2*columnas),sobrantesAuxiliar);
                    }else{combinacionesDetectadas--;}
                }
                else {
                    if(fichaMarcada(auxiliar,fv,sobrantesAuxiliar)){
                        marcarFicha(auxiliar,fv,sobrantesAuxiliar);
                    }else{combinacionesDetectadas--;}
                    if(fichaMarcada(auxiliar,fv+columnas,sobrantesAuxiliar)){
                        marcarFicha(auxiliar,fv+columnas,sobrantesAuxiliar);
                    }else{combinacionesDetectadas--;}
                    if(fichaMarcada(auxiliar,fv+(2*columnas),sobrantesAuxiliar)){
                        marcarFicha(auxiliar,fv+(2*columnas),sobrantesAuxiliar);
                    }else{combinacionesDetectadas--;}
                    combinacionesDetectadas++;
                }anterior=actual;
            }
        }realizarCaidas(tablero,filas,columnas,sobrantes,auxiliar,sobrantesAuxiliar, fichasEliminadas);
        delete[] auxiliar;
}


void realizarCaidas(unsigned char* tablero,int filas,int columnas,int sobrantes,unsigned char* auxiliar,int sobrantesAuxiliar, int& fichasEliminadas){

    for(int c=0; c<columnas; c++){
        int escritura=filas-1;
        for(int lectura=filas-1; lectura>=0; lectura--){
            int origen=lectura*columnas+c;
            if(fichaMarcada(auxiliar,origen,sobrantesAuxiliar)==1){
                unsigned char ficha=leerFicha(tablero, origen, sobrantes);
                int destino=escritura*columnas+c;
                if(origen!=destino){
                    escribirFicha(tablero, destino, sobrantes, ficha);
                }
                escritura--;
            }
            else{fichasEliminadas++;}
        }
        for(int f=escritura; f>=0; f--){
            int posicion=f*columnas+c;
            unsigned char ficha=rand()%6;
            escribirFicha(tablero, posicion, sobrantes, ficha);
        }
    }
}


void resolverCascadas(unsigned char* tablero,int filas,int columnas,int sobrantes,int& fichasEliminadas,int& combinacionesDetectadas,int& cascadasActuales){

    cascadasActuales = 0;
    int rondas = 0;

    while(true){
        int fichasAntes = fichasEliminadas;
        detectarCombinaciones(tablero, filas, columnas, sobrantes, fichasEliminadas, combinacionesDetectadas);
        if(fichasEliminadas == fichasAntes){
            break;
        }
        if(rondas > 0){
            cascadasActuales++;
        }
        rondas++;
    }
}

void mostrarPuntuacion(int fichasEliminadas, int combinacionesDetectadas){
    unsigned int puntuacion = fichasEliminadas*10 + combinacionesDetectadas*20;
    cout<<"Puntos: "<<puntuacion<<endl;

}
