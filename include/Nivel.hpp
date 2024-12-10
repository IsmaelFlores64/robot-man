#ifndef NIVEL_HPP
#define NIVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <stdexcept>

class Nivel {
private:
    sf::Texture tileset;
    sf::VertexArray vertices;
    int tileSize;

public:
    Nivel(const std::string& tilesetPath, const std::vector<std::vector<int>>& map, int tileSize);

    void draw(sf::RenderWindow& window);
};

#endif 
