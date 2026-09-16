#include "juego.h"
#include "bits.h"

bool marcarFicha(unsigned char* marcas, int posicion) {

    int byte = posicion / 8;
    int bit = 7 - posicion % 8;

    bool repetida = (marcas[byte] & (1 << bit)) == 0;

    marcas[byte] &= ~(1 << bit);

    return repetida;
}

int detectarCombinaciones(unsigned char* memoria,
                          unsigned char* marcas,
                          int filas, int columnas, int sobrantes) {

    int bytesMarcas = (filas * columnas + 7) / 8;

    // Todas las fichas comienzan con marca 1: conservar.
    for (int i = 0; i < bytesMarcas; i++) {
        marcas[i] = 255;
    }

    int combinaciones = 0;

    // Direccion 0: filas. Direccion 1: columnas.
    for (int direccion = 0; direccion < 2; direccion++) {

        int cantidadLineas;
        int longitud;
        int paso;

        if (direccion == 0) {
            cantidadLineas = filas;
            longitud = columnas;
            paso = 1;
        }
        else {
            cantidadLineas = columnas;
            longitud = filas;
            paso = columnas;
        }

        if (longitud < 3) {
            continue;
        }

        for (int linea = 0; linea < cantidadLineas; linea++) {

            int inicio;

            if (direccion == 0) {
                inicio = linea * columnas;
            }
            else {
                inicio = linea;
            }

            int posicionBit = sobrantes + inicio * 3;

            unsigned char* p1 = &memoria[posicionBit / 8];
            int bit1 = 7 - posicionBit % 8;

            unsigned char* p2 = p1;
            int bit2 = bit1;
            avanzarBits(p2, bit2, paso * 3);

            unsigned char* p3 = p2;
            int bit3 = bit2;
            avanzarBits(p3, bit3, paso * 3);

            unsigned char ficha1 = leerFicha(p1, bit1);
            unsigned char ficha2 = leerFicha(p2, bit2);
            unsigned char ficha3 = leerFicha(p3, bit3);

            bool anterior = false;
            int turno = 0;

            // Numero de la ultima ficha de la ventana, desde cero.
            int ultima = 2;

            while (true) {

                bool actual = ficha1 < 6 &&
                              ficha1 == ficha2 &&
                              ficha2 == ficha3;

                if (actual) {

                    if (!anterior) {
                        combinaciones++;

                        // Comienza un tramo: marcar sus tres fichas.
                        for (int j = ultima - 2; j <= ultima; j++) {

                            int posicion = inicio + j * paso;

                            if (marcarFicha(marcas, posicion)) {
                                combinaciones--;
                            }
                        }
                    }
                    else {
                        // Continua el tramo: marcar solo la nueva.
                        int posicion = inicio + ultima * paso;

                        if (marcarFicha(marcas, posicion)) {
                            combinaciones--;
                        }
                    }
                }

                int salto = 1;

                // Despues de A A A -> A A B,
                // podemos saltar la ventana A B ...
                if (anterior && !actual) {
                    salto = 2;
                }

                anterior = actual;

                // No salir de la fila o columna actual.
                if (ultima + salto >= longitud) {
                    break;
                }

                for (int avance = 0; avance < salto; avance++) {

                    // Cada puntero avanza tres fichas de la linea.
                    if (turno == 0) {
                        avanzarBits(p1, bit1, paso * 9);
                        ficha1 = leerFicha(p1, bit1);
                    }
                    else if (turno == 1) {
                        avanzarBits(p2, bit2, paso * 9);
                        ficha2 = leerFicha(p2, bit2);
                    }
                    else {
                        avanzarBits(p3, bit3, paso * 9);
                        ficha3 = leerFicha(p3, bit3);
                    }

                    ultima++;

                    turno++;
                    if (turno == 3) {
                        turno = 0;
                    }
                }
            }
        }
    }

    return combinaciones;
}
