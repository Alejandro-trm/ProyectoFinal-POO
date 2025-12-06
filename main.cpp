/*
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Segunda entrega del proyecto final: El juego de Blackjack
    Realizado por: 
                    Daniela Campo       2519451     daniela.campo.g@correounivalle.edu.co
                    Alejandro Trujillo  2516762     alejandro.melendez@correounivalle.edu.co
*/

#include "Juego.h"
#include <iostream>

using namespace std;

int main() {
    std::cout << "EL JUEGO DE BLACKJACK" << std::endl;
    Juego juego;
    juego.iniciarJuego();
    return 0;
}