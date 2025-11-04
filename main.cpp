/*
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Segunda entrega del proyecto final: El juego de Blackjack
    Realizado por: 
                    Daniela Campo       2519451     daniela.campo.g@correounivalle.edu.co
                    Alejandro Trujillo  2516762     alejandro.melendez@correounivalle.edu.co
*/

#include "Carta.h"
#include "Crupier.h"
#include "Juego.h"
#include "Jugador.h"
#include "Mano.h"
#include "Mazo.h"
#include "Persona.h"

#include <iostream>
using namespace std;

Crupier cr;
Juego j;
Jugador jugador;
Mano m;
Mazo mazo;
Persona p;

int main(){
    std::cout << "EL  JUEGO  DE BLACKJACK" << std::endl;
    Carta c = mazo.repartirCarta();

}