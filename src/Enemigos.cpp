#include <iostream>
#include <filesystem>
#include "Nivel.hpp"

Nivel::Nivel(const std::string& tilesetPath, const std::vector<std::vector<int>>& map, int tileSize)
    : tilemap(map, tileSize), enemigo({100.f, 100.f}, 16.f) {
    std::cout << "Ruta absoluta: " << std::filesystem::absolute(tilesetPath) << std::endl;

    if (!std::filesystem::exists(tilesetPath)) {
        std::cerr << "El archivo no existe: " << tilesetPath << std::endl;
        std::exit(1);
    }

    if (!tileset.loadFromFile(tilesetPath)) {
        std::cerr << "Error al cargar la textura desde: " << tilesetPath << std::endl;
        std::exit(1);
    }

    tilemap.setTexture(tileset);
}

void Nivel::procesarEventos(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Nivel::manejarEntrada() {
    // Aquí puedes añadir lógica para manejar la entrada del usuario
}

void Nivel::actualizar() {
    enemigo.actualizar();
}

void Nivel::dibujar(sf::RenderWindow& window) {
    tilemap.draw(window);
    enemigo.dibujar(window);
}
