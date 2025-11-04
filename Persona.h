/*
    Clase: Persona

    Responsabilidades:
        - Representar a una persona en el juego.
        - Proveer métodos para gestionar la mano de cartas del jugador.
        - Proveer métodos para gestionar las apuestas del jugador.
        
    Colaboradores:
        - Colabora con las clases `Mano`, `Jugador` y `Crupier`
        - Interactúa con la clase `Mano` para gestionar las cartas que posee la persona.
        - Colabora con la clase `Jugador` para representar a un jugador específico en el juego.
        - Colabora con la clase `Crupier` para gestionar la interacción entre el jugador y el crupier.
*/

#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include "Mano.h"

class Persona{
protected:
    std::string nombre;
    Mano mano;

public:
    void mostrarMano();
    int obtenerPuntaje();
    void nuevaMano();
};

#endif