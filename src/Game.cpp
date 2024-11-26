#include "Game.h"

// Definición del constructor
Game::Game()
    : circle(300.0f) // Inicializa el círculo con un radio de 300
{
}

// Método Begin: inicializa la posición del círculo
void Game::Begin(sf::RenderWindow& window) {
    circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius())); // Centro del círculo
    circle.setPosition(static_cast<sf::Vector2f>(window.getSize()) / 2.0f); // Centro de la ventana
}

// Método Update: lógica del juego (vacío por ahora)
void Game::Update(float deltaTime) {
    // Lógica de actualización (opcional)
}

// Método Render: dibuja el círculo en la ventana
void Game::Render(sf::RenderWindow& window) {
    window.draw(circle);
}
