#pragma once
#include <string>
#include <iostream>

#pragma once
#include <string>

class VistaConsola {
public:
    void mostrarMensaje(const std::string& mensaje);
    void mostrarLinea(const std::string& mensaje);
    std::string pedirEntrada(const std::string& prompt);
    double pedirNumero(const std::string& prompt);
};