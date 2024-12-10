#include "Nivel.hpp"
#include <iostream>

Nivel::Nivel(const std::string& tilesetPath, const std::vector<std::vector<int>>& map, int tileSize)
    : tileSize(tileSize) {
    // Cargar la textura del tileset
    if (!tileset.loadFromFile(tilesetPath)) {
        std::cerr << "Error cargando la textura desde: " << tilesetPath << std::endl;
        throw std::runtime_error("No se pudo cargar la textura del tileset.");
    }

    // Configurar el VertexArray
    int mapWidth = map[0].size();
    int mapHeight = map.size();
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(mapWidth * mapHeight * 4);


    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            int tileNumber = map[y][x];


            int tu = tileNumber % (tileset.getSize().x / tileSize);
            int tv = tileNumber / (tileset.getSize().x / tileSize);


            sf::Vertex* quad = &vertices[(x + y * mapWidth) * 4];

            quad[0].position = sf::Vector2f(x * tileSize, y * tileSize);
            quad[1].position = sf::Vector2f((x + 1) * tileSize, y * tileSize);
            quad[2].position = sf::Vector2f((x + 1) * tileSize, (y + 1) * tileSize);
            quad[3].position = sf::Vector2f(x * tileSize, (y + 1) * tileSize);

 
            quad[0].texCoords = sf::Vector2f(tu * tileSize, tv * tileSize);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize, (tv + 1) * tileSize);
            quad[3].texCoords = sf::Vector2f(tu * tileSize, (tv + 1) * tileSize);
        }
    }
}

void Nivel::draw(sf::RenderWindow& window) {
    sf::RenderStates states;
    states.texture = &tileset;
    window.draw(vertices, states);
}
