#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Bullet {
public:
    Bullet(sf::Vector2f startPosition, sf::Vector2f direction);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
    sf::Texture texture;
    b2Vec2 velocity;
};

#endif
