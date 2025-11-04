#include "Carta.h"

#include <iostream>

int Carta::getValor(){
    return valor;
}

std::string Carta::getNombre(){
    return nombre;
}

void Carta::setValor(int v){
    valor = v;
}

void Carta::setNombre(std::string n){
    nombre = n;
}