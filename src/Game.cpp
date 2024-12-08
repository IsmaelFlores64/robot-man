#include "Game.h"


Game::Game()
    : circle(300.0f) 
{
    circle.setFillColor(sf::Color::Green); 
}


void Game::Begin(sf::RenderWindow& window) {
   
    circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
    circle.setPosition(static_cast<sf::Vector2f>(window.getSize()) / 2.0f); 
}


void Game::Update(float deltaTime) {

}


void Game::Render(sf::RenderWindow& window) {
    window.draw(circle);
}

