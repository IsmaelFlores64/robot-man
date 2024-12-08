#include "Camara.h"


Camera::Camera(float zoomLevel)
    : zoomLevel(zoomLevel) {}


sf::View Camera::GetView(const sf::Vector2u& windowSize) const {
    sf::View view;
    view.setSize(windowSize.x * zoomLevel, windowSize.y * zoomLevel); // Aplica el zoom
    view.setCenter(windowSize.x / 2.0f, windowSize.y / 2.0f); // Centrar la vista
    return view;
}

