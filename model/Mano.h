/*
    Clase: Mano

    Responsabilidades:
        - Representar la mano de cartas de un jugador.
        - Proveer métodos para mostrar la mano de cartas.
        - Proveer métodos para determinar si contiene blackjack.

    Colaboradores:
        - Colabora con las clases `Persona` y `Carta`
        - Interactúa con la clase `Persona`, ya que cada persona tiene una mano de cartas.
        - Utiliza la clase `Carta` para conformar la mano del jugador.

*/

#ifndef MANO_H
#define MANO_H

#include <vector>
#include "Carta.h"

class Mano{
private:
    std::vector<Carta> cartas;

public:
    void agregarCarta(Carta c);
    int calcularValor();
    void mostrarMano(bool parcial);
    
    int contarCartas();
    bool tieneBlackjack();
    bool determinarBust();
};

#endif