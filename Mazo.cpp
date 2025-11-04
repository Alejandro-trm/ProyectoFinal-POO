#include "Mazo.h"

#include <iostream>
#include <algorithm>
#include <random>

Mazo::Mazo() {
    std::vector<std::string> nombres = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

    for (int i = 0; i < 4; i++) {
        for (std::string& nombre : nombres) {
            Carta c;
            c.setNombre(nombre);

            if (nombre == "A") c.setValor(11);
            else if (nombre == "J" || nombre == "Q" || nombre == "K") c.setValor(10);
            else c.setValor(std::stoi(nombre));

            cartas.push_back(c);
        }
    }
    std::shuffle(cartas.begin(), cartas.end(), std::mt19937(std::random_device{}()));
}

Carta Mazo::repartirCarta(){
    Carta c = cartas.back();
    cartas.pop_back();
    return c;
}

int Mazo::cartasRestantes(){
    return cartas.size();
}