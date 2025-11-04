/*
    Clase: Jugador

    Responsabilidades:
        - Proveer métodos para pedir cartas al Crupier durante su turno.
        - Proveer métodos para iniciar un nuevo juego
        - Proveer métodos para gestionar las apuestas del jugador.

    Colaboradores:
        - Colabora con las clases `Juego` y `Persona`
        - Representa a una persona que inició una partida de Blackjack.
        - Gestiona las solicitudes del jugador a través de la clase "Juego"
*/

#ifndef JUGADOR_H
#define JUGADOR_H

#include "Mazo.h"
#include "Persona.h"

class Jugador: public Persona{
private:
    double saldo;
    double apuesta;

public:
    void pedirCarta(Mazo& m);
    bool quiereOtraCarta();
    bool quiereNuevoJuego();
    void apostar(double monto);
    double getSaldo();
    double getApuesta();
    void cobrar(double monto);
    void devolverApuesta();
};

#endif