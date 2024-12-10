#include <SFML/Graphics.hpp>
#include "Nivel.hpp"

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "MegaMan Style Game");


    const std::vector<std::vector<int>> levelMap = {
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {3, 0, 0, 5, 5, 5, 0, 0, 0, 4},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        {6, 7, 7, 7, 7, 7, 7, 7, 7, 8}
    };


    Nivel nivel("assets/images/Desert-Retro-Lines.png", levelMap, 16);



    sf::RectangleShape player(sf::Vector2f(50.0f, 50.0f));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(375.0f, 300.0f);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();


        nivel.draw(window);
        window.draw(player);


        window.display();
    }

    return 0;
}
