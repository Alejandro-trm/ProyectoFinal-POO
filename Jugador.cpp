#include "Jugador.h"
#include <iostream>
#include <limits>

Jugador::Jugador(const std::string& nombre, double saldoInicial)
    : Persona(nombre), saldo(saldoInicial), apuesta(0) {}

void Jugador::pedirCarta(Mazo& m) {
    getMano().agregarCarta(m.repartirCarta());
}

bool Jugador::quiereOtraCarta() {
    char opcion;
    std::cout << "¿Deseas otra carta? (s/n): ";
    std::cin >> opcion;
    return (opcion == 's' || opcion == 'S');
}

bool Jugador::quiereNuevoJuego() {
    char opcion;
    std::cout << "¿Deseas iniciar un nuevo juego? (s/n): ";
    std::cin >> opcion;
    return (opcion == 's' || opcion == 'S');
}

void Jugador::apostar(double monto) {
    while (monto > saldo || monto <= 0 || std::cin.fail()) {
        std::cout << "Apuesta inválida. Tu saldo es $" << saldo << ". Ingresa una apuesta válida: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> monto;
    }
    apuesta = monto;
    saldo -= monto;
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