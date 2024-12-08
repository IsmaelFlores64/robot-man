#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera {
public:
    explicit Camera(float zoomLevel); 
    sf::View GetView(const sf::Vector2u& windowSize) const; 

private:
    float zoomLevel; 
};

#endif 

