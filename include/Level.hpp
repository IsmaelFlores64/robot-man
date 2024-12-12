#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Level {
public:
    Level(const sf::Vector2u& windowSize);  // Constructor

    void initPlatforms(const sf::Vector2u& windowSize);  // Iniciar plataformas
    void addAdditionalPlatforms(const sf::Vector2u& windowSize);  // Añadir plataformas adicionales
    void update(float deltaTime);  // Actualizar el nivel (plataformas en movimiento)
    void draw(sf::RenderWindow& window);  // Dibujar el nivel

private:
    void updateMovingPlatforms(float deltaTime);  // Función privada para actualizar plataformas móviles

    std::vector<sf::RectangleShape> platforms;  // Contenedor para las plataformas
};

#endif
