#include "Persona.h"

Persona::Persona(const std::string& nombre) : nombre(nombre), mano() {}

void Persona::mostrarMano(bool parcial){
    mano.mostrarMano(parcial);
}

int Persona::obtenerPuntaje(){
    return mano.calcularValor();
}

void Persona::nuevaMano(){
    mano = Mano();
}

std::string Persona::getNombre() const {
    return nombre;
}

Mano& Persona::getMano() {
    return mano;
}