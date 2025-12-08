#include "Jugador.h"
#include <iostream>
#include <limits>

Jugador::Jugador(const std::string& nombre, double saldoInicial)
    : Persona(nombre), saldo(saldoInicial), apuesta(0) {}

bool Jugador::quiereOtraCarta() {
    char opcion;
    std::cout << "¿Deseas otra carta? (s/n): ";
    std::cin >> opcion;
    return (opcion == 's' || opcion == 'S');
}

bool Jugador::quiereNuevoJuego() {
    char opcion;
    std::cout << nombre << ", ¿Deseas iniciar un nuevo juego? (s/n): ";
    std::cin >> opcion;
    return (opcion == 's' || opcion == 'S');
}

void Jugador::apostar(double monto) {
    try {
        if (monto <= 0)
            throw std::invalid_argument("La apuesta debe ser mayor a 0.");

        if (monto > saldo)
            throw std::runtime_error("Saldo insuficiente para apostar esa cantidad.");

        if (std::cin.fail())
            throw std::runtime_error("Entrada inválida.");

        apuesta = monto;
        saldo -= monto;
    }
    catch (const std::exception& e) {
        std::cout << "Error en la apuesta: " << e.what() << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double Jugador::getSaldo() {
    return saldo;
}

double Jugador::getApuesta() {
    return apuesta;
}

void Jugador::cobrar(double monto) {
    saldo += monto;
}

void Jugador::devolverApuesta() {
    saldo += apuesta;
    apuesta = 0;
}
void Jugador::reiniciarApuesta() {
    apuesta = 0;
}