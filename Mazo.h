/*
    Clase: Mazo

    Responsabilidades:
        - Almacena un mazo de cartas 
        - Provee métodos para barajar cartas.
        - Provee métodos calcular las cartas restantes luego de repartir.
        
    Colaboradores:
        - Colabora con las clases `Carta` y `Juego`
        - Interactúa con la clase `Carta` para gestionar las cartas en el mazo.
        - Utiliza la clase `Juego` para integrar la lógica del juego con el mazo de cartas.
*/

#ifndef MAZO_H
#define MAZO_H

#include <vector>
#include "Carta.h"

class Mazo{
private:
    std::vector<Carta> cartas;

public:
    Mazo();
    Carta repartirCarta();
    int cartasRestantes();
};

#endif