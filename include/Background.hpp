#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Background
{
public:
    Background(const std::string &imagePath);
    void draw(sf::RenderWindow &window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif // BACKGROUND_HPP