#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <iostream>
#include <filesystem>

class Enemigo {
public:
    Enemigo(const std::string& textureFile, float speed, int screenWidth)
        : speed(speed), screenWidth(screenWidth) {
        if (!texture.loadFromFile(textureFile)) {
            throw std::runtime_error("Failed to load texture file");
        }
        sprite.setTexture(texture);
        sprite.setScale(2.0f, 2.0f); 
    }

    void update(float deltaTime) {
        sf::Vector2f position = sprite.getPosition();
        position.x -= speed * deltaTime;

        if (position.x + sprite.getGlobalBounds().width < 0) {
            position.x = static_cast<float>(screenWidth);
        }

        sprite.setPosition(position);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    int screenWidth;
};

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    const float enemigoSpeed = 200.0f; 
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Enemigo Animation");
    window.setFramerateLimit(60);


    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    Enemigo enemigo("./assets/images/blue_slime.png", enemigoSpeed, screenWidth);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
        }

        float deltaTime = clock.restart().asSeconds();

        enemigo.update(deltaTime);

        window.clear();
        enemigo.draw(window);
        window.display();
    }

    return 0;
}
