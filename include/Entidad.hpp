#ifndef ENTIDAD_HPP
#define ENTIDAD_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Entidad {
public:
    virtual ~Entidad() = default;
    virtual void actualizar() = 0;
    virtual void dibujar(sf::RenderWindow& ventana) = 0;
};

#endif
