#ifndef BITS_H
#define BITS_H


int byteficha(int indice,int sobrantes);

int bitficha(int indice, int sobrantes);

unsigned char leerFicha(unsigned char* puntero, int bit, int sobrantes);

void escribirFicha(unsigned char* puntero, int posicionLineal, int sobrantes, unsigned char ficha);

#endif
