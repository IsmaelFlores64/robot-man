#include "Level.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

// Constructor de la clase Level
Level::Level(const sf::Vector2u& windowSize) {
    // Intentar cargar la textura de fondo
    std::cout << "Cargando fondo: C:/ruta/completa/a/tu/proyecto/assets/images/Future.png" << std::endl;
    if (!backgroundTexture.loadFromFile("C:/ruta/completa/a/tu/proyecto/assets/images/Future.png")) {
        std::cerr << "Error loading background image!" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);  // Asignar la textura a un sprite
    }

    // Intentar cargar la textura de la plataforma de fondo (Ground)
    std::cout << "Cargando Ground: C:/ruta/completa/a/tu/proyecto/assets/images/Ground.png" << std::endl;
    if (!groundTexture.loadFromFile("C:/ruta/completa/a/tu/proyecto/assets/images/Ground.png")) {
        std::cerr << "Error loading ground image!" << std::endl;
    }

    // Intentar cargar la textura para las plataformas adicionales (future_city.png)
    std::cout << "Cargando Future City: C:/ruta/completa/a/tu/proyecto/assets/images/future_city.png" << std::endl;
    if (!platformTexture.loadFromFile("C:/ruta/completa/a/tu/proyecto/assets/images/future_city.png")) {
        std::cerr << "Error loading future_city image!" << std::endl;
    }

    initPlatforms(windowSize);  // Inicializar las plataformas
}

void Level::initPlatforms(const sf::Vector2u& windowSize) {
    // Crear la plataforma base con la imagen de fondo (Ground)
    sf::RectangleShape ground(sf::Vector2f(windowSize.x, 50));  // Plataforma base a lo largo de la ventana
    if (groundTexture.getSize().x != 0 && groundTexture.getSize().y != 0) {
        ground.setTexture(&groundTexture);  // Asignar la textura al rectángulo
    } else {
        ground.setFillColor(sf::Color(139, 69, 19));  // Color marrón en caso de error
    }
    ground.setPosition(0, windowSize.y - 50);  // Posición en la parte inferior de la ventana
    platforms.push_back(ground);

    // Crear plataformas adicionales con la textura future_city.png
    sf::RectangleShape platform1(sf::Vector2f(200, 20));
    if (platformTexture.getSize().x != 0 && platformTexture.getSize().y != 0) {
        platform1.setTexture(&platformTexture);  // Asignar la textura de future_city
    } else {
        platform1.setFillColor(sf::Color::Green);  // Color verde en caso de error
    }
    platform1.setPosition(200, 400);
    platforms.push_back(platform1);

    sf::RectangleShape platform2(sf::Vector2f(200, 20));
    if (platformTexture.getSize().x != 0 && platformTexture.getSize().y != 0) {
        platform2.setTexture(&platformTexture);  // Asignar la textura de future_city
    } else {
        platform2.setFillColor(sf::Color::Blue);  // Color azul en caso de error
    }
    platform2.setPosition(600, 300);
    platforms.push_back(platform2);

    sf::RectangleShape platform3(sf::Vector2f(200, 20));
    if (platformTexture.getSize().x != 0 && platformTexture.getSize().y != 0) {
        platform3.setTexture(&platformTexture);  // Asignar la textura de future_city
    } else {
        platform3.setFillColor(sf::Color::Yellow);  // Color amarillo en caso de error
    }
    platform3.setPosition(1000, 200);
    platforms.push_back(platform3);

    // Plataformas móviles (sin imágenes de fondo)
    sf::RectangleShape movingPlatform1(sf::Vector2f(200, 20));
    movingPlatform1.setFillColor(sf::Color::Red);
    movingPlatform1.setPosition(1200, 150);
    movingPlatform1.setOrigin(movingPlatform1.getSize().x / 2, movingPlatform1.getSize().y / 2);
    platforms.push_back(movingPlatform1);

    sf::RectangleShape movingPlatform2(sf::Vector2f(200, 20));
    movingPlatform2.setFillColor(sf::Color::Cyan);
    movingPlatform2.setPosition(1600, 100);
    movingPlatform2.setOrigin(movingPlatform2.getSize().x / 2, movingPlatform2.getSize().y / 2);
    platforms.push_back(movingPlatform2);

    // Llamar a la función para añadir plataformas adicionales
    addAdditionalPlatforms(windowSize);
}

void Level::addAdditionalPlatforms(const sf::Vector2u& windowSize) {
    // Crear plataformas adicionales con la textura future_city.png
    sf::RectangleShape platform4(sf::Vector2f(200, 20));
    if (platformTexture.getSize().x != 0 && platformTexture.getSize().y != 0) {
        platform4.setTexture(&platformTexture);  // Asignar la textura de future_city
    } else {
        platform4.setFillColor(sf::Color(255, 165, 0)); // Naranja en caso de error
    }
    platform4.setPosition(2000, 300);
    platforms.push_back(platform4);

    sf::RectangleShape platform5(sf::Vector2f(200, 20));
    if (platformTexture.getSize().x != 0 && platformTexture.getSize().y != 0) {
        platform5.setTexture(&platformTexture);  // Asignar la textura de future_city
    } else {
        platform5.setFillColor(sf::Color(128, 0, 128)); // Morado en caso de error
    }
    platform5.setPosition(2400, 400);
    platforms.push_back(platform5);

    sf::RectangleShape platform6(sf::Vector2f(200, 20));
    if (platformTexture.getSize().x != 0 && platformTexture.getSize().y != 0) {
        platform6.setTexture(&platformTexture);  // Asignar la textura de future_city
    } else {
        platform6.setFillColor(sf::Color(255, 255, 0)); // Amarillo en caso de error
    }
    platform6.setPosition(2800, 500);
    platforms.push_back(platform6);
}

void Level::update(float deltaTime) {
    // Actualizar las plataformas móviles
    updateMovingPlatforms(deltaTime);
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
    // Dibujar el fondo
    window.draw(backgroundSprite);

    // Dibujar todas las plataformas
    for (auto& platform : platforms) {
        window.draw(platform);
    }
}
