#include "Crupier.h"
#include "Jugador.h"
#include "Mano.h"
#include <iostream>
#include <string>

Crupier::Crupier(const std::string& nombre) : Persona(nombre) {}

void Crupier::repartirInicial(std::vector<Jugador>& jugadores, Mazo& mazo) {
    for (auto& jugador : jugadores) {
        jugador.getMano().agregarCarta(mazo.repartirCarta());
        jugador.getMano().agregarCarta(mazo.repartirCarta());
    }
}

void Crupier::mostrarMano(bool parcial) {
    mano.mostrarMano(parcial);
}

int Crupier::obtenerPuntaje() {
    return Persona::obtenerPuntaje();
}