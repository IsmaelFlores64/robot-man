#include "Bullet.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

Bullet::Bullet(sf::Vector2f startPosition, sf::Vector2f direction) {
    // Cargar la textura de la bala
    if (!texture.loadFromFile("assets/images/bullet.png")) {
        std::cerr << "Error al cargar la textura de la bala" << std::endl;
    }

    // Configurar el sprite de la bala
    sprite.setTexture(texture);
    sprite.setPosition(startPosition);

    // Convertir la dirección de SFML a Box2D
    velocity = b2Vec2(direction.x * 10.0f, direction.y * 10.0f);  // Multiplicar por un factor de velocidad
}

void Bullet::update(float deltaTime) {
    // Actualizar la posición de la bala (esto depende de la velocidad)
    sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
