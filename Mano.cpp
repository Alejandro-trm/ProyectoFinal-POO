#include "Mano.h"

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

void Mano::mostrarMano(){
    for (Carta& c : cartas) {
        std::cout << c.getNombre() << c.getValor() << "  ";
    }
    std::cout << std::endl;
}

bool Mano::tieneBlackjack(){
    return (contarCartas() == 2 && calcularValor() == 21);
}

bool Mano::determinarBust(){
    return (calcularValor() > 21);
}