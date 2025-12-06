/*
    Clase: Crupier

    Responsabilidades:
        - Gestionar el mazo de cartas y la distribución de cartas a los jugadores.
        - Proveer métodos para mostrar una mano de cartas.
        - Controlar los turnos del juego y revisar el puntaje
        - Proveer métodos para calcular valores y determinar si un jugador tiene blackjack.

    Colaboradores:
        - Colabora con las clases `Juego` y `Persona`
        - Utiliza la clase `Juego` para controlar el flujo del juego según las reglas
        - Interactúa con la clase `Persona` para revisar los valores de su mano y decidir si inicia una nueva partida.
*/

#ifndef CRUPIER_H
#define CRUPIER_H

#include <vector>
#include "Mazo.h"
#include "Jugador.h"
#include "Persona.h"

class Crupier : public Persona{
public:

    Crupier(const std::string& nombre = "Crupier");

    void repartirInicial(std::vector<Jugador>& jugadores, Mazo& m);
    void jugarTurno(Mazo& m);
    int obtenerPuntaje();
    void mostrarMano(bool parcial);
    void mostrarParcial();
    int calcularValorVisible();
    bool tieneBlackjack();
};

#endif