#include "Mano.h"
#include "Carta.h"
#include <iostream>

void Mano::agregarCarta(Carta c){
    cartas.push_back(c);
}

int Mano::calcularValor(){
    int total = 0;
    int ases = 0;

    for (Carta& c : cartas) {
        int valor = c.getValor();

        if (valor == 11) {
            ases++;
        }

        total += valor;
    }

    while (total > 21 && ases > 0) {
        total -= 10;
        ases--;
    }

    return total;
}

int Mano::contarCartas(){
    return cartas.size();
}

void Mano::mostrarMano(bool parcial) {
    auto mostrarCarta = [](const Carta& c) {
        std::string nombre = c.getNombre();
        if (nombre == "A" || nombre == "J" || nombre == "Q" || nombre == "K") {
             std::cout << nombre << " (" << c.getValor() << ")  ";
        } else {
            std::cout << c.getValor() << "  ";
        }
    };

    if (parcial && !cartas.empty()) {
        mostrarCarta(cartas[0]);
        std::cout << "[Carta oculta]" << std::endl;
    } else {
        for (Carta& c : cartas) {
            mostrarCarta(c);
        }
        std::cout << std::endl;
    }
}

bool Mano::tieneBlackjack(){
    return (contarCartas() == 2 && calcularValor() == 21);
}

bool Mano::determinarBust(){
    return (calcularValor() > 21);
}