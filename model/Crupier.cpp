#include "Crupier.h"
#include "Jugador.h"
#include "Mano.h"
#include <iostream>
#include <string>
#include <stdexcept>

Crupier::Crupier(const std::string& nombre) : Persona(nombre) {}

void Crupier::repartirInicial(std::vector<Jugador>& jugadores, Mazo& mazo) {
    try {
        for (auto& jugador : jugadores) {
            if (mazo.cartasRestantes() < 2){
                throw std::runtime_error("No hay suficientes cartas en el mazo para repartir.");
            }
            jugador.getMano().agregarCarta(mazo.repartirCarta());
            jugador.getMano().agregarCarta(mazo.repartirCarta());
        }
    }
    catch (const std::exception& e) {
        std::cout << "Error al repartir cartas iniciales: " << e.what() << "\n";
    }
}

void Crupier::mostrarMano(bool parcial) {
    mano.mostrarMano(parcial);
}

bool Crupier::tieneBlackjack(){
    return mano.tieneBlackjack();
}

int Crupier::obtenerPuntaje() {
    return Persona::obtenerPuntaje();
}