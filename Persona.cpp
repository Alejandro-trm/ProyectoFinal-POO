#include "Persona.h"

void Persona::mostrarMano(){
    mano.mostrarMano();
}

int Persona::obtenerPuntaje(){
    return mano.calcularValor();
}

void Persona::nuevaMano(){
    mano = Mano();
}