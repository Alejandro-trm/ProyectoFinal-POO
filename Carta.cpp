#include "Carta.h"
#include <iostream>


int Carta::getValor() const{
    return valor;
}

std::string Carta::getNombre() const{
    return nombre;
}

void Carta::setValor(int v){
    valor = v;
}

void Carta::setNombre(std::string n){
    nombre = n;
}