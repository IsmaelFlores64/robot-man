#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "MegaMan Style Game");


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


        window.draw(player);


        window.display();
    }

    return 0;
}

