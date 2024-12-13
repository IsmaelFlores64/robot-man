#include "Level.hpp"
#include <iostream>

Level::Level(const sf::Vector2u& windowSize, b2World& mundo, Robotman& robotman)
    : robotman(robotman)
{
    // Cargar la imagen de fondo
    std::cout << "Cargando fondo: ./assets/images/Future.png" << std::endl;
    if (!backgroundTexture.loadFromFile("./assets/images/Future.png"))
    {
        std::cerr << "Error al cargar la imagen de fondo!" << std::endl;
        backgroundRectangle.setSize(sf::Vector2f(windowSize.x, windowSize.y));  // Configurar el tamaño del fondo
        backgroundRectangle.setFillColor(sf::Color::Black);  // Fondo negro en caso de error
    }
    else
    {
        backgroundSprite.setTexture(backgroundTexture);  // Usar la textura cargada
    }

    // Cargar otras texturas
    if (!groundTexture.loadFromFile("./assets/images/Ground.png"))
    {
        std::cerr << "Error al cargar la imagen de Ground!" << std::endl;
    }
    if (!platformTexture.loadFromFile("./assets/images/future_city.png"))
    {
        std::cerr << "Error al cargar la imagen de platform!" << std::endl;
    }

    initPlatforms(windowSize, mundo);  // Llamar a la función para inicializar las plataformas
}

void Level::initPlatforms(const sf::Vector2u& windowSize, b2World& mundo)
{
    for (int i = 0; i < 3; ++i)
    {
        sf::Sprite platform;
        platform.setTexture(platformTexture);
        platform.setPosition(100.0f + i * 200.0f, windowSize.y - 100.0f);
        platforms.push_back(platform);

        // Crear cuerpo físico para la plataforma
        b2BodyDef bodyDef;
        bodyDef.type = b2_kinematicBody;
        bodyDef.position.Set(platform.getPosition().x, platform.getPosition().y);
        b2Body* platformBody = mundo.CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(platform.getGlobalBounds().width / 2.0f, platform.getGlobalBounds().height / 2.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        platformBody->CreateFixture(&fixtureDef);
    }
}

void Level::updateMovingPlatforms(float deltaTime)
{
    for (auto& platform : platforms)
    {
        sf::Vector2f position = platform.getPosition();
        platform.move(50.0f * deltaTime, 0.0f);  // Movimiento de la plataforma

        // Regresar la plataforma al inicio cuando alcance el borde derecho
        if (position.x > 800.0f)
        {
            platform.setPosition(-platform.getLocalBounds().width, position.y);
        }
    }
}

void Level::update(float deltaTime)
{
    updateMovingPlatforms(deltaTime);  // Actualizar las plataformas móviles
    robotman.update(deltaTime);  // Actualizar el robotman
}

void Level::draw(sf::RenderWindow& window)
{
    // Dibujar el fondo
    if (backgroundTexture.getSize().x == 0 || backgroundTexture.getSize().y == 0)
    {
        window.draw(backgroundRectangle);  // Dibujar fondo negro si no se carga la imagen
    }
    else
    {
        window.draw(backgroundSprite);  // Dibujar fondo con la textura cargada
    }

    // Dibujar las plataformas
    for (auto &platform : platforms)
    {
        window.draw(platform);
    }

    // Dibujar las balas
    robotman.draw(window);  // Asegúrate de que `draw` esté implementado en `Robotman`
}
