#include "VistaConsola.h"
#include <iostream>

void VistaConsola::mostrarMensaje(const std::string& mensaje) {
    std::cout << mensaje;
}

void VistaConsola::mostrarLinea(const std::string& mensaje) {
    std::cout << mensaje << std::endl;
}

std::string VistaConsola::pedirEntrada(const std::string& prompt) {
    std::cout << prompt;
    std::string entrada;
    std::cin >> entrada;
    return entrada;
}

double VistaConsola::pedirNumero(const std::string& prompt) {
    double valor;
    std::cout << prompt;
    std::cin >> valor;
    return valor;
}