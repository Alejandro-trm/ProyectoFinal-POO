/*
    Clase: Carta

    Responsabilidades:
        - Representar una carta en el sistema, incluyendo su contenido y valores asociados.
        - proveer métodos para obtener el nombre y valor de la carta.
        - Proveer métodos para asignar nombre y valor a la carta.

    Colaboradores:
        - Colabora con las clases `Mano` y `Mazo` ya que cada carta está asociada al mazo de 
          cartas y además conforma la mano del jugador.
        - Agrupa cartas de la clase "Mazo" 
        - Hace parte de la "Mano" del jugador
*/

#ifndef CARTA_H
#define CARTA_H

#include <string>

class Carta{
private:
  int valor;
  std::string nombre;
  
public:
  int getValor() const;
  std::string getNombre() const;
  void setValor(int v);
  void setNombre(std::string n);

};

#endif