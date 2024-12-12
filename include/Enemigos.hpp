#ifndef ENEMIGOS_HPP
#define ENEMIGOS_HPP

#include <SFML/Graphics.hpp>

class Enemigos {
public:
    Enemigos(const sf::Vector2f& posicionInicial, float radio);
    void actualizar();
    void dibujar(sf::RenderWindow& window);

private:
    sf::CircleShape bola; // Representa al enemigo como una bola simple
    sf::Vector2f velocidad;
};

#endif

