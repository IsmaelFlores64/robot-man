#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
    // Configuración inicial de la ventana y el juego
    Game game;
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Megaman");
    sf::Clock deltaClock; // Reloj para medir deltaTime

    game.Begin(window); // Configuración inicial del juego

    // Bucle principal del juego
    while (window.isOpen()) {
        // Calcula el tiempo transcurrido desde el último frame
        float deltaTime = deltaClock.restart().asSeconds();

        // Manejo de eventos
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Cierra la ventana
            }
        }

        // Lógica del juego
        game.Update(deltaTime);

        // Renderizado
        window.clear();        // Limpia la pantalla
        game.Render(window);   // Dibuja los elementos del juego
        window.display();      // Muestra en la pantalla
    }

    return 0;
}
