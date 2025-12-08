#include "Mazo.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <stdexcept>

Mazo::Mazo() {
    try {
        std::vector<std::string> nombres = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

        for (int i = 0; i < 4; i++) {
            for (std::string& nombre : nombres) {
                Carta c;
                c.setNombre(nombre);

                if (nombre == "A") {
                    c.setValor(11);
                }
                else if (nombre == "J" || nombre == "Q" || nombre == "K") {
                    c.setValor(10);
                }
                else {
                    c.setValor(std::stoi(nombre));
                }
                cartas.push_back(c);
            }
        }
        if (cartas.size() != 52)
            throw std::runtime_error("Error al generar el mazo: tamaño incorrecto.");
        std::shuffle(cartas.begin(), cartas.end(), std::mt19937(std::random_device{}()));
    }
    catch (const std::exception& e) {
        std::cout << "Error en la construcción del mazo: " << e.what() << "\n";
    }
}

Carta Mazo::repartirCarta(){
    try {
        if (cartas.empty())
            throw std::out_of_range("No hay cartas para repartir.");

        Carta c = cartas.back();
        cartas.pop_back();
        return c;
    }
    catch (const std::exception& e) {
        std::cout << "Error al repartir carta: " << e.what() << "\n";
        return Carta();
    }
}

int Mazo::cartasRestantes()const {
    return cartas.size();
}