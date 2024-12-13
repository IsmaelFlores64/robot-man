#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game(); // Constructor
    void Begin(sf::RenderWindow &window);
    void Update(float deltaTime);
    void Render(sf::RenderWindow &window);

private:
    sf::CircleShape circle;
};

#endif
