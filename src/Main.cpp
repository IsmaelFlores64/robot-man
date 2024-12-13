#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <stdexcept>
#include "Level.hpp"
#include "Menu.hpp"
#include "Robotman.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Plataforma con SFML");

    Menu menu;
    b2World mundo(b2Vec2(0.0f, 9.8f)); // Gravedad hacia abajo

    // Cargar la textura de Robotman
    sf::Texture robotmanTexture;
    if (!robotmanTexture.loadFromFile("assets/images/Robot.png")) {
        std::cerr << "Error al cargar la textura de Robotman" << std::endl;
        return -1;
    }

    // Crear el objeto Robotman y pasarle el mundo y la textura
    Robotman robotman(mundo, robotmanTexture, 400.0f, 300.0f);

    // Crear el objeto Level y pasar el objeto robotman
    Level level(window.getSize(), mundo, robotman);

    try {
        menu.playMusic();

        while (window.isOpen()) {
            int action = menu.handleInput(window);

            if (action == 1) { // JUGAR
                sf::Clock clock;

                while (window.isOpen()) {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                            window.close();

                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                            robotman.disparar();  // Llamar a la función disparar del objeto robotman
                        }

                        // Control de movimiento
                        if (event.type == sf::Event::KeyPressed) {
                            if (event.key.code == sf::Keyboard::Left) {
                                robotman.setVelocity(-5.f, robotman.getVelocity().y);  // Mover a la izquierda
                            } else if (event.key.code == sf::Keyboard::Right) {
                                robotman.setVelocity(5.f, robotman.getVelocity().y);   // Mover a la derecha
                            }
                        }

                        // Detener movimiento cuando se suelta la tecla
                        if (event.type == sf::Event::KeyReleased) {
                            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                                robotman.setVelocity(0.f, robotman.getVelocity().y);  // Detener el movimiento
                            }
                        }
                    }

                    float deltaTime = clock.restart().asSeconds();
                    mundo.Step(deltaTime, 8, 3); // Actualizar física

                    robotman.update(deltaTime); // Actualizar Robotman

                    window.clear(sf::Color::Cyan);
                    level.update(deltaTime); // Actualizar plataformas móviles y balas
                    level.draw(window); // Dibujar nivel
                    robotman.draw(window); // Dibujar robotman y sus balas
                    window.display();
                }
            }

            window.clear();
            menu.draw(window);
            window.display();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return -1;
    }

    return 0;
}
