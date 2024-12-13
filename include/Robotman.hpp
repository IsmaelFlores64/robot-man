#ifndef ROBOTMAN_HPP
#define ROBOTMAN_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include "Bullet.hpp"  // Incluye el encabezado de Bullet

class Robotman {
public:
    Robotman(b2World& world, const sf::Texture& texture, float startX, float startY);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;
    void disparar();

private:
    b2World& mundo;
    b2Body* body;
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    std::vector<Bullet> bullets;  // Vector de balas
};

#endif
