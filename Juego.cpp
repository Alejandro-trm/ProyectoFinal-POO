#include "Juego.h"
#include <iostream>
#include <limits>
#include <stdexcept>

void Juego::iniciarJuego() {
    std::cout << "¡Es momento de apostar!\n";

        // Preguntar la cantidad de jugadores
        int cantidad = 0;
        while (true) {
            try {
                std::cout << "\n¿Cuántos jugadores van a participar? (1-7): ";
                std::cin >> cantidad;
                std::cout << "\n";

                if (std::cin.fail() || cantidad < 1 || cantidad > 7) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Entrada inválida: Debes ingresar un número entre 1 y 7.");
                }
                break;
            } catch (const std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        jugadores.clear();
        //Pedir los nombres de los jugadores
        for (int i = 0; i < cantidad; ++i) {
            std::string nombre;
            std::cout << "Nombre del jugador " << (i+1) << ": ";
            std::cin >> nombre;
            jugadores.emplace_back(nombre, 1000); // saldo inicial
        }
    
        
        bool continuarPartida = true;
        while(continuarPartida){
            std::cout << "\n";
            for (Jugador& j : jugadores) {
                double monto;
                while (true) {
                    try {
                        std::cout << j.getNombre() << ", tu saldo es de $" 
                                << j.getSaldo() << ". Ingresa tu apuesta: ";
                        std::cin >> monto;

                        if (std::cin.fail() || monto <= 0 || monto > j.getSaldo()) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            throw std::invalid_argument("Apuesta inválida. Debe ser un valor positivo y no mayor a tu saldo.");
                        }
                        j.apostar(monto);
                        break;
                        
                    } catch (const std::invalid_argument& e) {
                        std::cout << "Error: " << e.what() << "\n";
                    }
                }
            }
        
        repartirCartasIniciales();
        turnoJugadores();
        turnoCrupier();
        evaluarResultados();

        continuarPartida = continuarJuego();
    }
    std::cout << "\n---FIN DEL JUEGO---\n";
}

void Juego::repartirCartasIniciales() {
    // Crear nuevo mazo y reiniciar crupier
    mazo = Mazo();
    crupier.nuevaMano();
    
    for (Jugador& j : jugadores) {
        j.nuevaMano();
    }

    //El crupier reparte las cartas iniciales a los jugadores
    crupier.repartirInicial(jugadores,mazo);
    crupier.pedirCarta(mazo);
    crupier.pedirCarta(mazo);

    //Se muestra la mano de cada jugador
    for (Jugador&j: jugadores){
        std::cout << "\n" << j.getNombre() << " recibe: ";
        j.mostrarMano();
        std::cout << "Puntaje: " << j.obtenerPuntaje() << "\n";
    }

    std::cout << "\nCrupier muestra: ";
    crupier.mostrarMano(true);
}

void Juego::turnoJugadores(){
    for (Jugador& jugador : jugadores) {
    std::cout << "\n==============================\n";
    std::cout << "Turno de " << jugador.getNombre() << "\n";
    std::cout << "------------------------------\n";
    
    jugador.mostrarMano();
    std::cout << "Puntaje: " << jugador.obtenerPuntaje() << "\n";

        while (!jugador.getMano().determinarBust() && jugador.quiereOtraCarta()) {
           try {
                jugador.pedirCarta(mazo);
                std::cout << "\nTu mano ahora:\n";
                jugador.mostrarMano();
                std::cout << "Puntaje: " << jugador.obtenerPuntaje() << "\n";
            } catch (const std::exception& e) {
                    std::cout << "Error al pedir carta: " << e.what() << std::endl;
                    break;
                }
        }
        if (jugador.getMano().determinarBust()) {
            std::cout << "¡Te has pasado de 21!\n";
        }
    }
}

void Juego::turnoCrupier(){
    std::cout << "\n==============================\n";
    std::cout << "Turno del crupier:\n";
    std::cout << "------------------------------\n";
    crupier.mostrarMano(false);
    
    while (crupier.obtenerPuntaje() < 17) {
        std::cout << "El crupier pide carta...\n";
        crupier.getMano().agregarCarta(mazo.repartirCarta());
        crupier.mostrarMano(false);
        std::cout << "Puntaje del crupier: " << crupier.obtenerPuntaje() << "\n";
    }
    
    if (crupier.getMano().determinarBust()) {
        std::cout << "¡El crupier se ha pasado de 21!\n";
    }
}

void Juego::evaluarResultados() {
    int puntajeCrupier = crupier.obtenerPuntaje();
    bool crupierBust = crupier.getMano().determinarBust();

    std::cout << "\n";
    
    for (Jugador& jugador : jugadores) {
        int puntajeJugador = jugador.obtenerPuntaje();
        bool jugadorBust = jugador.getMano().determinarBust();

        std::cout << "Resultado para " << jugador.getNombre() << ": ";
        
        if (jugadorBust) {
            std::cout << "Te has pasado de 21. Pierdes.\n";
        } else if (crupierBust) {
            std::cout << "El crupier se pasó de 21. ¡Ganas!\n";
        } else if (puntajeJugador > puntajeCrupier) {
            std::cout << "¡Ganas!\n";
        } else if (puntajeJugador < puntajeCrupier) {
            std::cout << "Pierdes.\n";
        } else {
            std::cout << "Empate.\n";
        }
        resolverPagos(jugador);
    }
}

void Juego::resolverPagos(Jugador& jugador) {
    int puntajeCrupier = crupier.obtenerPuntaje();
    bool crupierBust = crupier.getMano().determinarBust();
    int puntajeJugador = jugador.obtenerPuntaje();
    bool jugadorBust = jugador.getMano().determinarBust();

    if (jugadorBust) {
        std::cout << jugador.getNombre() << " pierde su apuesta de $" << jugador.getApuesta() << ". Saldo: $" << jugador.getSaldo() << "\n";
    } else if (crupierBust || puntajeJugador > puntajeCrupier) {
        double ganancia = jugador.getApuesta() * 2;
        jugador.cobrar(ganancia);
        std::cout << jugador.getNombre() << " gana $" << ganancia << ". Saldo: $" << jugador.getSaldo() << "\n";
    } else if (puntajeJugador == puntajeCrupier) {
        jugador.devolverApuesta();
        std::cout << jugador.getNombre() << " empata y recupera su apuesta. Saldo: $" << jugador.getSaldo() <<  "\n";
    } else {
        std::cout << jugador.getNombre() << " pierde su apuesta de $" << jugador.getApuesta() << ". Saldo: $" << jugador.getSaldo() << ".\n";
    }
    std::cout << "\n";
    // Reinicia la apuesta para la siguiente ronda
    jugador.reiniciarApuesta();
}

bool Juego::continuarJuego(){
    std::vector<Jugador> jugadoresSiguienteRonda;
    for (Jugador& jugador : jugadores) {

        if (jugador.getSaldo() <= 0) {
            std::cout << jugador.getNombre() << " no tiene saldo suficiente para continuar.\n";
            continue;
        }

        if (jugador.quiereNuevoJuego()) {
            jugadoresSiguienteRonda.push_back(jugador);
        }
    }

    if (jugadoresSiguienteRonda.empty()) {
        std::cout << "No hay jugadores que deseen continuar.\n";
        return false;
    }

    jugadores = jugadoresSiguienteRonda;

    return true;
}