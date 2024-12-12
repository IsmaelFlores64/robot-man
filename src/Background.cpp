// main.cpp
#include <SFML/Graphics.hpp>
#include "Background.hpp"
#include <iostream>

Background::Background(const std::string& imagePath) {
    if (!texture.loadFromFile(imagePath)) {
        throw std::runtime_error("Failed to load background image");
    }
    sprite.setTexture(texture);
}

void Background::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

int main() {
    const std::string imagePath = "Background.webp"; // Replace with the correct image path

    sf::RenderWindow window(sf::VideoMode(800, 600), "Background Example");

    try {
        Background background(imagePath);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            background.draw(window);
            window.display();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
