## Datos del proyecto Blackjack en C++
Autores: 
    Daniela Campo      2519451  daniela.campo.g@correounivalle.edu.co
    Alejandro Trujillo 2516762  alejandro.melendez@correounivalle.edu.co

Curso:
    Fundamentos de programación orientada a objetos
    Tecnología en desarrollo de software
    Universidad del Valle

Año:
    2025

## 🔹 Introducción
El proyecto se desarrolla como entrega final para el curso de programación orientada a objetos e implementa una versión simplificada del juego Blackjack en el lenguaje C++. Su objetivo es aplicar conceptos de encapsulamiento, herencia y, en general, los principios de la POO; a través de clases que modelan los elementos fundamentales del juego.

## 🔹 Descripción general del funcionamiento y organización
En la partida simulada de Blackjack, intervienen un jugador y un crupier por medio de quienes se gestionan el mazo, las manos y las reglas del juego.

El sistema se conforma por las siguientes clases:
    - Carta: Representa una carta individual, con sus atributos nombre y valor.
    - Mazo: Contiene las 52 cartas del juego y permite repartirlas de manera aleatoria.
    - Mano: Almacena las cartas de un jugador o del crupier y calcula su valor total.
    - Persona: Clase base para Jugador y Crupier, que incluye el nombre y la mano asociada.
    - Jugador: Hereda de Persona. Permite pedir cartas, realizar apuestas y decidir si continuar o retirarse.
    - Crupier: Hereda de Persona. Controla el mazo, reparte cartas y sigue las reglas de la casa.
    - Juego: Gestiona el flujo general del juego, desde la inicialización hasta la determinación del ganador.

## 🔹 Ejecución del programa
    1. Abrir el proyecto en Visual Studio Code.
    2. Asegurarse de abrir el programa dentro del entorno Dev Container.
    3. Dentro del Dev Container:
        make           # Compila con símbolos de depuración
        make run       # Ejecuta el binario
        make clean     # Limpia binarios