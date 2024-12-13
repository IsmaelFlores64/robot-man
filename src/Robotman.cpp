#include "Robotman.hpp"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

Robotman::Robotman(b2World& world, const sf::Texture& texture, float startX, float startY)
    : mundo(world), texture(texture), speed(10.0f) {

    // Crear el cuerpo de Box2D para Robotman
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(startX, startY);
    body = mundo.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(50.0f, 100.0f);  // Tamaño de Robotman

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    // Asignar la textura y el sprite
    sprite.setTexture(texture);
    sprite.setOrigin(50.f, 100.f);  // Ajuste del sprite (según las dimensiones del cuerpo)
}

void Robotman::update(float deltaTime) {
    // Actualizar la posición de sprite basada en la física de Box2D
    b2Vec2 pos = body->GetPosition();
    sprite.setPosition(pos.x, pos.y);

    // Actualizar balas
    for (auto& bullet : bullets) {
        bullet.update(deltaTime);  // Actualiza cada bala
    }
}

void Robotman::draw(sf::RenderWindow& window) {
    window.draw(sprite);

    // Dibujar las balas
    for (auto& bullet : bullets) {
        bullet.draw(window);
    }
}

void Robotman::setVelocity(float vx, float vy) {
    b2Vec2 velocity(vx, vy);
    body->SetLinearVelocity(velocity);  // Establecer la velocidad del cuerpo
}

sf::Vector2f Robotman::getVelocity() const {
    b2Vec2 velocity = body->GetLinearVelocity();
    return sf::Vector2f(velocity.x, velocity.y);
}

void Robotman::disparar() {
    // Crear una nueva bala y agregarla al vector de balas
    b2Vec2 position = body->GetPosition();
    b2Vec2 direction(1.f, 0.f);  // Dirección de disparo (a la derecha, por ejemplo)
    Bullet newBullet(sf::Vector2f(position.x, position.y), sf::Vector2f(direction.x, direction.y));
    bullets.push_back(newBullet);  // Agregar la nueva bala al vector
}
