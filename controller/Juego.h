/*
    Clase: Juego

    Responsabilidades:
        - Iniciar el juego
        - Repartir las cartas iniciales a través del Crupier
        - Provee métodos para determinar el ganador de la partida.
        - Provee métodos para reiniciar el juego y preparar una nueva partida.

    Colaboradores:
        - Colabora con las clases `Crupier`, `Mazo` y `Jugador`
        - Controla el juego mediante la clase "Crupier"
        - Utiliza la clase "Mazo" para gestionar las cartas del juego.
        - Gestiona las solicitudes del jugador a través de la clase "Jugador"
*/

#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include "../model/Mazo.h"
#include "../model/Crupier.h"
#include "../model/Jugador.h"
#include "../view/VistaConsola.h"

class Juego{
private:
    Mazo mazo;
    std::vector<Jugador> jugadores;
    Crupier crupier;
    VistaConsola vista;

public:
    void iniciarJuego();
    void repartirCartasIniciales();
    void turnoJugadores();
    void turnoCrupier();
    void evaluarResultados();
    void resolverPagos(Jugador& jugador, const std::string& resultado);
    bool continuarJuego();
};

#endif