#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Level {
public:
    Level(const sf::Vector2u& windowSize);
    void initPlatforms(const sf::Vector2u& windowSize);
    void addAdditionalPlatforms(const sf::Vector2u& windowSize);
    void update(float deltaTime);
    void updateMovingPlatforms(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture backgroundTexture;
    sf::Texture groundTexture;
    sf::Texture platformTexture; // Declaración de platformTexture
    sf::Sprite backgroundSprite;
    std::vector<sf::RectangleShape> platforms;
};

#endif
