#include <SFML/Graphics.hpp>
#include "Level.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Plataforma con SFML");

    Level level(window.getSize());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Cyan); // Fondo azul cielo
        level.draw(window);
        window.display();
    }

    return 0;
}
