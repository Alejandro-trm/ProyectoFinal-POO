#include "Juego.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <iomanip>

void Juego::iniciarJuego() {
    vista.mostrarLinea("¡Es momento de apostar!\n");

        // Preguntar la cantidad de jugadores
        int cantidad = 0;
        while (true) {
            try {
                cantidad = vista.pedirNumero("¿Cuántos jugadores van a participar? (1-7): ");
                vista.mostrarLinea("");

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
            nombre = vista.pedirEntrada("Nombre del jugador " + std::to_string(i + 1) + ": ");
            jugadores.emplace_back(nombre, 1000); // saldo inicial
        }
    
        
        bool continuarPartida = true;
        while(continuarPartida){
            vista.mostrarLinea("");
            for (Jugador& j : jugadores) {
                double monto;
                while (true) {
                    try {
                        std::ostringstream oss;
                        oss << j.getNombre() << ", tu saldo es de $" << static_cast<int>(j.getSaldo()) << ". Ingresa tu apuesta: ";
                        monto = vista.pedirNumero(oss.str());

                        if (std::cin.fail() || monto <= 0 || monto > j.getSaldo()) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            throw std::invalid_argument("Apuesta inválida. Debe ser un valor positivo y no mayor a tu saldo.\n");
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
    vista.mostrarLinea("\n---FIN DEL JUEGO---\n");
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
        vista.mostrarLinea("");
        vista.mostrarMensaje(j.getNombre() + " recibe: ");
        j.mostrarMano();
        vista.mostrarLinea("Puntaje: " + std::to_string(j.obtenerPuntaje()));
    }

    vista.mostrarLinea("\nCrupier muestra: ");
    crupier.mostrarMano(true);
}

void Juego::turnoJugadores(){
    for (Jugador& jugador : jugadores) {
    vista.mostrarLinea("==============================");
    vista.mostrarLinea("Turno de " + jugador.getNombre());
    vista.mostrarLinea("------------------------------");
    
    jugador.mostrarMano();
    vista.mostrarLinea("Puntaje: " + std::to_string(jugador.obtenerPuntaje()));

        while (!jugador.getMano().determinarBust() && jugador.quiereOtraCarta()) {
           try {
                jugador.pedirCarta(mazo);
                vista.mostrarLinea("\nTu mano ahora:");
                jugador.mostrarMano();
                vista.mostrarLinea("Puntaje: " + std::to_string(jugador.obtenerPuntaje()));
            } catch (const std::exception& e) {
                    vista.mostrarLinea("Error al pedir carta: " + std::string(e.what()));
                    break;
                }
        }
        if (jugador.getMano().determinarBust()) {
            vista.mostrarLinea("¡Te has pasado de 21!");
        }
    }
}

void Juego::turnoCrupier(){
    vista.mostrarLinea("\n==============================\n");
    vista.mostrarLinea("Turno del crupier:");
    vista.mostrarLinea("------------------------------");
    crupier.mostrarMano(false);
    
    while (crupier.obtenerPuntaje() < 17) {
        vista.mostrarLinea("El crupier pide carta...");
        crupier.getMano().agregarCarta(mazo.repartirCarta());
        crupier.mostrarMano(false);
        vista.mostrarLinea("Puntaje del crupier: " + std::to_string(crupier.obtenerPuntaje()));
    }
    
    if (crupier.getMano().determinarBust()) {
        vista.mostrarLinea("¡El crupier se ha pasado de 21!");
    }
}

void Juego::evaluarResultados() {
    int puntajeCrupier = crupier.obtenerPuntaje();
    bool crupierBust = crupier.getMano().determinarBust();

    std::cout << "\n";
    
    for (Jugador& jugador : jugadores) {
        int puntajeJugador = jugador.obtenerPuntaje();
        bool jugadorBust = jugador.getMano().determinarBust();

        vista.mostrarMensaje("Resultado para " + jugador.getNombre() + ": ");
        
        if (jugadorBust) {
            vista.mostrarLinea("Te has pasado de 21. Pierdes.");
        } else if (crupierBust) {
            vista.mostrarLinea("El crupier se pasó de 21. ¡Ganas!");
        } else if (puntajeJugador > puntajeCrupier) {
            vista.mostrarLinea("¡Ganas!");
        } else if (puntajeJugador < puntajeCrupier) {
            vista.mostrarLinea("Pierdes.");
        } else {
            vista.mostrarLinea("Empate.");
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
            vista.mostrarLinea(jugador.getNombre() + " pierde su apuesta de $" + std::to_string(static_cast<int>(jugador.getApuesta())) + ". Saldo: $" + std::to_string(static_cast<int>(jugador.getSaldo())));
        } else if (crupierBust || puntajeJugador > puntajeCrupier) {
            double ganancia = jugador.getApuesta() * 2;
            jugador.cobrar(ganancia);
            vista.mostrarLinea(jugador.getNombre() + " gana $" + std::to_string(static_cast<int>(ganancia)) + ". Saldo: $" + std::to_string(static_cast<int>(jugador.getSaldo())));
        } else if (puntajeJugador == puntajeCrupier) {
            jugador.devolverApuesta();
            vista.mostrarLinea(jugador.getNombre() + " empata y recupera su apuesta. Saldo: $" + std::to_string(static_cast<int>(jugador.getSaldo())));
        } else {
            vista.mostrarLinea(jugador.getNombre() + " pierde su apuesta de $" + std::to_string(static_cast<int>(jugador.getApuesta())) + ". Saldo: $" + std::to_string(static_cast<int>(jugador.getSaldo())));
        }
            vista.mostrarLinea("");
            // Reinicia la apuesta para la siguiente ronda
            jugador.reiniciarApuesta();
}

bool Juego::continuarJuego(){
    std::vector<Jugador> jugadoresSiguienteRonda;
    for (Jugador& jugador : jugadores) {

        if (jugador.getSaldo() <= 0) {
            vista.mostrarLinea(jugador.getNombre() + " no tiene saldo suficiente para continuar.");
            continue;
        }

        if (jugador.quiereNuevoJuego()) {
            jugadoresSiguienteRonda.push_back(jugador);
        }
    }

    if (jugadoresSiguienteRonda.empty()) {
        vista.mostrarLinea("No hay jugadores que deseen continuar.");
        return false;
    }

    jugadores = jugadoresSiguienteRonda;

    return true;
}