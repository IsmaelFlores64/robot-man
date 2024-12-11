#ifndef NIVEL_HPP
#define NIVEL_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <iostream>

class Nivel {
public:
    Nivel(b2World& mundo, sf::RenderWindow& ventana);

    void cargarTilemap(const std::string& texturaPath, const std::vector<std::vector<int>>& mapa, int tileSize);
    void agregarBola(const sf::Vector2f& posicion, float radio);

    void procesarEventos();
    void manejarEntrada();
    void actualizar();
    void dibujar();

private:
    b2World& mundo;
    sf::RenderWindow& ventana;
    sf::View camara;

    sf::Texture texturaTilemap;
    sf::Sprite spriteTilemap;
    std::vector<std::vector<int>> mapa;
    int tileSize;

    b2Body* bola;
    sf::CircleShape formaBola;

    int fuerzaMovimiento;
    bool puedeSaltar;
};

#endif // NIVEL_HPP
