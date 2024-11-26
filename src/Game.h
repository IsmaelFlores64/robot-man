#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:
    sf::CircleShape circle; // Atributo interno para renderizar un círculo

public:
    Game(); // Constructor
    void Begin(sf::RenderWindow& window);
    void Update(float deltaTime);
    void Render(sf::RenderWindow& window);
};