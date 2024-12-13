#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Robotman.hpp"
#include <vector>

class Level {
public:
    Level(const sf::Vector2u& windowSize, b2World& mundo, Robotman& robotman);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    void initPlatforms(const sf::Vector2u& windowSize, b2World& mundo);  // Declaración de initPlatforms
    void updateMovingPlatforms(float deltaTime);  // Declaración de updateMovingPlatforms

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape backgroundRectangle;

    sf::Texture groundTexture;
    sf::Texture platformTexture;

    std::vector<sf::Sprite> platforms;
    Robotman& robotman;
};

#endif
