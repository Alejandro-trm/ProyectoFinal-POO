#include "Juego.h"
#include "Crupier.h"
#include "Jugador.h"
#include "Mazo.h"
#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>

#include <iostream>

void Juego::iniciarJuego() {
    std::cout << "Es momento de apostar, bienvenido a Blackjack!\n";
    std::cout << "¿Deseas iniciar la partida? (s/n): ";
    char opcion;
    std::cin >> opcion;

    if (opcion == 's' || opcion == 'S') {
        // Validar cantidad de jugadores
       // ...dentro de Juego::iniciarJuego()

        int cantidad = 0;
        while (true) {
            try {
                std::cout << "¿Cuántos jugadores van a participar? (1-7): ";
                std::cin >> cantidad;
                if (std::cin.fail() || cantidad < 1 || cantidad > 7) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Entrada inválida: Debes ingresar un número entre 1 y 7.");
                }
                break; // Entrada válida, sal del bucle
            } catch (const std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        for (int i = 0; i < cantidad; ++i) {
            std::string nombre;
            std::cout << "Nombre del jugador " << (i+1) << ": ";
            std::cin >> nombre;
            jugadores.push_back(Jugador(nombre, 1000)); // saldo inicial
        }

       for (auto& jugador : jugadores) { // Pedir apuestas
        double monto;
        while (true) {
            try {
                std::cout << jugador.getNombre() << ", ingresa tu apuesta: ";
                std::cin >> monto;
                if (std::cin.fail() || monto <= 0 || monto > jugador.getSaldo()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Apuesta inválida. Debes ingresar un monto positivo y no mayor a tu saldo.");
                }
                jugador.apostar(monto);
                break; // Apuesta válida, sal del bucle
            } catch (const std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
}
        repartirCartasIniciales();
        jugarRonda();
        determinarGanador();
        resolverPagos();
        reiniciarJuego();
    } else {
        std::cout << "Saliendo del juego.\n";
    }
}

void Juego::repartirCartasIniciales() {
   try {
        // Reparte dos cartas a cada jugador
        crupier.repartirInicial(jugadores, mazo);

        // Reparte dos cartas al crupier (a sí mismo)
        crupier.getMano().agregarCarta(mazo.repartirCarta());
        crupier.getMano().agregarCarta(mazo.repartirCarta());

        // Muestra la mano inicial de cada jugador
        for (auto& jugador : jugadores) {
            std::cout << "\n==============================\n";
            std::cout << "Jugador: " << jugador.getNombre() << "\n";
            std::cout << "------------------------------\n";
            jugador.mostrarMano(false);
            std::cout << "Puntaje: " << jugador.obtenerPuntaje() << "\n";
            std::cout << "==============================\n";
        }
        std::cout << "\n==============================\n";
        std::cout << "Crupier muestra:\n";
        crupier.mostrarMano(true); // true = mostrar solo una carta
        std::cout << "==============================\n";

    } catch (const std::exception& e) {
        std::cerr << "Error al repartir cartas iniciales: " << e.what() << std::endl;
    }
}

void Juego::jugarRonda() {
    // Turno de cada jugador
    for (auto& jugador : jugadores) {
    std::cout << "\n==============================\n";
    std::cout << "Turno de " << jugador.getNombre() << "\n";
    std::cout << "------------------------------\n";
    jugador.mostrarMano(false);

        while (!jugador.getMano().determinarBust() && jugador.quiereOtraCarta()) {
           try {
                jugador.pedirCarta(mazo);
                std::cout << "Tu mano ahora:\n";
                jugador.mostrarMano(false);
                std::cout << "Puntaje: " << jugador.obtenerPuntaje() << "\n";
            } catch (const std::exception& e) {
                    std::cout << "Error al pedir carta: " << e.what() << std::endl;
                    break;
                }
        }
        if (jugador.getMano().determinarBust()) {
            std::cout << "¡Te has pasado de 21!\n";
        }
        std::cout << std::endl;
    }

    // Turno del crupier
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
    std::cout << std::endl;
}

void Juego::determinarGanador() {
    int puntajeCrupier = crupier.obtenerPuntaje();
    bool crupierBust = crupier.getMano().determinarBust();

    for (auto& jugador : jugadores) {
        std::cout << "\n------------------------------\n";
        std::cout << "Resultado para " << jugador.getNombre() << ": ";

        int puntajeJugador = jugador.obtenerPuntaje();
        bool jugadorBust = jugador.getMano().determinarBust();

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
    }
}

void Juego::resolverPagos() {
    int puntajeCrupier = crupier.obtenerPuntaje();
    bool crupierBust = crupier.getMano().determinarBust();

    for (auto& jugador : jugadores) {
        std::cout << "\n------------------------------\n";
        int puntajeJugador = jugador.obtenerPuntaje();
        bool jugadorBust = jugador.getMano().determinarBust();

        if (jugadorBust) {
            std::cout << jugador.getNombre() << " pierde su apuesta de $" << jugador.getApuesta() << ".\n";
        } else if (crupierBust || puntajeJugador > puntajeCrupier) {
            double ganancia = jugador.getApuesta() * 2;
            jugador.cobrar(ganancia);
            std::cout << jugador.getNombre() << " gana $" << ganancia << ". Nuevo saldo: $" << jugador.getSaldo() << "\n";
        } else if (puntajeJugador == puntajeCrupier) {
            jugador.devolverApuesta();
            std::cout << jugador.getNombre() << " empata y recupera su apuesta. Saldo: $" << jugador.getSaldo() << "\n";
        } else {
            std::cout << jugador.getNombre() << " pierde su apuesta de $" << jugador.getApuesta() << ".\n";
        }
        // Reinicia la apuesta para la siguiente ronda SIN pedir entrada
        jugador.reiniciarApuesta();
    }
}

void Juego::reiniciarJuego(){
    std::vector<Jugador> jugadoresSiguienteRonda;

    for (auto& jugador : jugadores) {

        if (jugador.getSaldo() <= 0) {
            std::cout << jugador.getNombre() << " no tiene saldo suficiente para continuar.\n";
            continue;
        }

        if (jugador.quiereNuevoJuego()) {
            jugador.nuevaMano();
            jugadoresSiguienteRonda.push_back(jugador);
        }
    }

    if (jugadoresSiguienteRonda.empty()) {
        std::cout << "No hay jugadores que deseen continuar.\n";
        return;
    }

    jugadores = jugadoresSiguienteRonda;
    crupier.nuevaMano();
    mazo = Mazo(); // nuevo mazo mezclado

    // Pedir nuevas apuestas
    for (auto& jugador : jugadores) {
        double monto;
        while (true) {
            try {
                std::cout << jugador.getNombre() << ", ingresa tu nueva apuesta: ";
                std::cin >> monto;
                if (std::cin.fail() || monto <= 0 || monto > jugador.getSaldo()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Apuesta inválida. Debes ingresar un monto positivo y no mayor a tu saldo.");
                }
                jugador.apostar(monto);
                break;
            } catch (const std::invalid_argument& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    }

    repartirCartasIniciales();
    jugarRonda();
    determinarGanador();
    resolverPagos();
    reiniciarJuego();
}