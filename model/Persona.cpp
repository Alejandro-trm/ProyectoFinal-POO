#include "Persona.h"
#include <iostream>
#include <exception>

Persona::Persona(const std::string& nombre) : nombre(nombre), mano() {}

void Persona::mostrarMano(){
    mano.mostrarMano(false);
}

int Persona::obtenerPuntaje(){
    return mano.calcularValor();
}

void Persona::nuevaMano(){
    mano = Mano();
}

void Persona::pedirCarta(Mazo& m) {
    try {
        if (m.cartasRestantes() == 0)
            throw std::runtime_error("No hay cartas para repartir.");

        getMano().agregarCarta(m.repartirCarta());
    }
    catch (const std::exception& e) {
        std::cout << "Error al pedir carta: " << e.what() << "\n";
    }
}

std::string Persona::getNombre() const {
    return nombre;
}

Mano& Persona::getMano() {
    return mano;
}