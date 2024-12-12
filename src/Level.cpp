#include "Level.hpp"

Level::Level(const sf::Vector2u& windowSize) {
    initPlatforms(windowSize);  // Llamar a la función para inicializar plataformas
}

void Level::initPlatforms(const sf::Vector2u& windowSize) {
    // Crear una plataforma base extendida a lo largo de la nueva ventana
    sf::RectangleShape ground(sf::Vector2f(windowSize.x, 50));  // Plataforma extendida a lo largo del largo de la ventana
    ground.setFillColor(sf::Color(139, 69, 19)); // Marrón
    ground.setPosition(0, windowSize.y - 50);  // Posición al fondo
    platforms.push_back(ground);

    // Crear plataformas más pequeñas, esparcidas a lo largo del largo
    sf::RectangleShape platform1(sf::Vector2f(200, 20));  // Plataforma 1 extendida de largo
    platform1.setFillColor(sf::Color::Green);
    platform1.setPosition(200, 400);  // Esparcida
    platforms.push_back(platform1);

    sf::RectangleShape platform2(sf::Vector2f(200, 20));  // Plataforma 2 extendida de largo
    platform2.setFillColor(sf::Color::Blue);
    platform2.setPosition(600, 300);  // Esparcida
    platforms.push_back(platform2);

    sf::RectangleShape platform3(sf::Vector2f(200, 20));  // Plataforma 3 extendida de largo
    platform3.setFillColor(sf::Color::Yellow);
    platform3.setPosition(1000, 200);  // Esparcida
    platforms.push_back(platform3);

    // Plataformas móviles
    sf::RectangleShape movingPlatform1(sf::Vector2f(200, 20));  // Plataforma móvil 1 extendida de largo
    movingPlatform1.setFillColor(sf::Color::Red);
    movingPlatform1.setPosition(1200, 150);  // Esparcida
    movingPlatform1.setOrigin(movingPlatform1.getSize().x / 2, movingPlatform1.getSize().y / 2);
    platforms.push_back(movingPlatform1);

    sf::RectangleShape movingPlatform2(sf::Vector2f(200, 20));  // Plataforma móvil 2 extendida de largo
    movingPlatform2.setFillColor(sf::Color::Cyan);
    movingPlatform2.setPosition(1600, 100);  // Esparcida
    movingPlatform2.setOrigin(movingPlatform2.getSize().x / 2, movingPlatform2.getSize().y / 2);
    platforms.push_back(movingPlatform2);

    // Llamar a la función para añadir plataformas adicionales
    addAdditionalPlatforms(windowSize);
}

void Level::addAdditionalPlatforms(const sf::Vector2u& windowSize) {
    // Crear plataformas adicionales, esparcidas a lo largo del largo
    sf::RectangleShape platform4(sf::Vector2f(200, 20));  // Plataforma adicional 1
    platform4.setFillColor(sf::Color(255, 165, 0)); // Naranja
    platform4.setPosition(2000, 300);  // Esparcida
    platforms.push_back(platform4);

    // Cambiar el color 'Purple' por un color válido
    sf::RectangleShape platform5(sf::Vector2f(200, 20));  // Plataforma adicional 2
    platform5.setFillColor(sf::Color(128, 0, 128)); // Morado (RGB)
    platform5.setPosition(2400, 400);  // Esparcida
    platforms.push_back(platform5);

    sf::RectangleShape platform6(sf::Vector2f(200, 20));  // Plataforma adicional 3
    platform6.setFillColor(sf::Color(255, 255, 0)); // Amarillo
    platform6.setPosition(2800, 500);  // Esparcida
    platforms.push_back(platform6);
}

void Level::update(float deltaTime) {
    // Actualizar las plataformas móviles
    updateMovingPlatforms(deltaTime);  // Llamar a la función que actualiza las plataformas móviles
}

void Level::updateMovingPlatforms(float deltaTime) {
    for (auto& platform : platforms) {
        if (platform.getFillColor() == sf::Color::Red) {
            // Mover la plataforma roja de izquierda a derecha
            sf::Vector2f position = platform.getPosition();
            float speed = 100.0f; // Velocidad de movimiento
            platform.setPosition(position.x + speed * deltaTime, position.y);
            if (position.x > 900 || position.x < 100) {
                platform.move(-2 * speed * deltaTime, 0); // Cambiar dirección
            }
        }
        if (platform.getFillColor() == sf::Color::Cyan) {
            // Mover la plataforma cian hacia arriba y hacia abajo
            sf::Vector2f position = platform.getPosition();
            float speed = 60.0f; // Velocidad de movimiento
            platform.setPosition(position.x, position.y + speed * deltaTime);
            if (position.y > 300 || position.y < 50) {
                platform.move(0, -2 * speed * deltaTime); // Cambiar dirección
            }
        }
    }
}

void Level::draw(sf::RenderWindow& window) {
    // Dibujar todas las plataformas
    for (auto& platform : platforms) {
        window.draw(platform);
    }
}
