#include "Nivel.hpp"

Nivel::Nivel(b2World& mundo, sf::RenderWindow& ventana)
    : mundo(mundo), ventana(ventana), fuerzaMovimiento(10), puedeSaltar(false), tileSize(0) {
    camara = sf::View(sf::FloatRect(0, 0, ventana.getSize().x, ventana.getSize().y));
}

void Nivel::cargarTilemap(const std::string& texturaPath, const std::vector<std::vector<int>>& mapa, int tileSize) {
    this->mapa = mapa;
    this->tileSize = tileSize;

    if (!texturaTilemap.loadFromFile(texturaPath)) {
        std::cerr << "Error al cargar la textura del tilemap." << std::endl;
    }

    spriteTilemap.setTexture(texturaTilemap);
}

void Nivel::agregarBola(const sf::Vector2f& posicion, float radio) {
    b2BodyDef cuerpoDef;
    cuerpoDef.type = b2_dynamicBody;
    cuerpoDef.position.Set(posicion.x, posicion.y);
    bola = mundo.CreateBody(&cuerpoDef);

    b2CircleShape forma;
    forma.m_radius = radio;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &forma;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.7f;
    fixtureDef.restitution = 0.0f;
    bola->CreateFixture(&fixtureDef);

    formaBola = sf::CircleShape(radio);
    formaBola.setFillColor(sf::Color::Red);
}

void Nivel::procesarEventos() {
    sf::Event evento;
    while (ventana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed)
            ventana.close();
    }
}

void Nivel::manejarEntrada() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        bola->ApplyLinearImpulse(b2Vec2(-fuerzaMovimiento, 0), bola->GetWorldCenter(), true);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        bola->ApplyLinearImpulse(b2Vec2(fuerzaMovimiento, 0), bola->GetWorldCenter(), true);
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && puedeSaltar) {
        bola->ApplyLinearImpulse(b2Vec2(0, -20.0f), bola->GetWorldCenter(), true);
        puedeSaltar = false;
    }
}

void Nivel::actualizar() {
    mundo.Step(1.0f / 60.0f, 6, 2);

    // Verificar colisión con el suelo basado en el tilemap
    puedeSaltar = false;
    b2Vec2 posicionBola = bola->GetPosition();
    int tileX = static_cast<int>(posicionBola.x) / tileSize;
    int tileY = static_cast<int>(posicionBola.y + formaBola.getRadius()) / tileSize;

    if (tileY >= 0 && tileY < mapa.size() && tileX >= 0 && tileX < mapa[tileY].size() && mapa[tileY][tileX] == 1) {
        puedeSaltar = true;
    }

    camara.setCenter(posicionBola.x, posicionBola.y);
    ventana.setView(camara);
}

void Nivel::dibujar() {
    for (size_t y = 0; y < mapa.size(); ++y) {
        for (size_t x = 0; x < mapa[y].size(); ++x) {
            int tile = mapa[y][x];
            if (tile >= 0) {
                spriteTilemap.setTextureRect(sf::IntRect(tile * tileSize, 0, tileSize, tileSize));
                spriteTilemap.setPosition(x * tileSize, y * tileSize);
                ventana.draw(spriteTilemap);
            }
        }
    }

    formaBola.setPosition(bola->GetPosition().x, bola->GetPosition().y);
    ventana.draw(formaBola);
}
