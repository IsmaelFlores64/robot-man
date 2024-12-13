#ifndef ENEMIGO_HPP
#define ENEMIGO_HPP

#include <SFML/Graphics.hpp>

class Enemigo {
public:
    Enemigo(const std::string& textureFile, float speed, int screenWidth);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    int screenWidth;
};

#endif 
