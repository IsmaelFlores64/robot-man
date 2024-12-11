#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Nivel.hpp"

int main() {
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Nivel con Tilemap");
    b2Vec2 gravedad(0.0f, 10.0f);
    b2World mundo(gravedad);

    Nivel nivel(mundo, ventana);

std::vector<std::vector<int>> level = {
    {26, 26, 6, 7, 26, 26, 5, 26, 26, 8, 9, 26, 5, 26, 26, 26},
    {-1, -1, -1, -1, -1, 8, 9, -1, 5, -1, -1, -1, -1, -1, -1, 8, 9, -1, 5,},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},       
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, -1, -1, 0, 1,},
};
    nivel.cargarTilemap("./assets/images/Full-Retro-Lines-Tiles.png", mapa, 16);
    nivel.agregarBola({50.0f, 50.0f}, 8.0f);

    while (ventana.isOpen()) {
        nivel.procesarEventos();
        nivel.manejarEntrada();
        nivel.actualizar();

        ventana.clear();
        nivel.dibujar();
        ventana.display();
    }

    return 0;
}
