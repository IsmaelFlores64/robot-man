#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>

int main()
{
    int fuerza = 10;  // Fuerza de movimiento
    bool puedeSaltar = false;

    // Crear una ventana de SFML
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Nivel con Linea Invisible");

    // Crear una vista (cámara)
    sf::View camara(sf::FloatRect(0, 0, 800, 600));

    // Crear un mundo de Box2D
    b2Vec2 vectorGravedad(0.0f, 10.0f);  // Gravedad
    b2World mundo(vectorGravedad);

    // Crear las plataformas en nuevas posiciones
    std::vector<b2Body*> plataformas;
    std::vector<sf::RectangleShape> formasPlataformas;

    // Nuevas posiciones de plataformas
    std::vector<sf::Vector2f> plataformasPosiciones = {
        {100.0f, 500.0f}, {250.0f, 450.0f}, {400.0f, 400.0f}, {550.0f, 350.0f},
        {700.0f, 300.0f}, {150.0f, 250.0f}, {350.0f, 200.0f}, {600.0f, 150.0f}
    };

    // Crear las plataformas en Box2D
    for (const auto& pos : plataformasPosiciones)
    {
        // Crear un cuerpo estático para cada plataforma
        b2BodyDef cuerpoPlataformaDef;
        cuerpoPlataformaDef.position.Set(pos.x, pos.y);
        b2Body* cuerpoPlataforma = mundo.CreateBody(&cuerpoPlataformaDef);

        // Crear una forma rectangular para la plataforma
        b2PolygonShape formaPlataforma;
        formaPlataforma.SetAsBox(100.0f / 2.0f, 10.0f / 2.0f);

        // Agregar la forma al cuerpo
        b2FixtureDef fixturePlataformaDef;
        fixturePlataformaDef.shape = &formaPlataforma;
        fixturePlataformaDef.friction = 1.0f;
        cuerpoPlataforma->CreateFixture(&fixturePlataformaDef);

        plataformas.push_back(cuerpoPlataforma);

        // Crear una forma SFML para representar la plataforma
        sf::RectangleShape plataforma(sf::Vector2f(100.0f, 10.0f));
        plataforma.setOrigin(50.0f, 5.0f);
        plataforma.setPosition(pos);
        plataforma.setFillColor(sf::Color::Green); // Color verde para las plataformas
        formasPlataformas.push_back(plataforma);
    }

    // Crear un cuerpo dinámico (la bola)
    b2BodyDef cuerpoBolaDef;
    cuerpoBolaDef.type = b2_dynamicBody;
    cuerpoBolaDef.position.Set(200.0f, 400.0f); // Posición inicial sobre una plataforma
    b2Body* cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);

    // Crear una forma circular para la bola
    b2CircleShape formaBola;
    formaBola.m_radius = 25.0f;

    // Agregar la forma al cuerpo
    b2FixtureDef fixtureBolaDef;
    fixtureBolaDef.shape = &formaBola;
    fixtureBolaDef.density = 1.0f;
    fixtureBolaDef.friction = 0.7f;
    fixtureBolaDef.restitution = 0.0f; // Sin rebote
    cuerpoBola->CreateFixture(&fixtureBolaDef);

    // Crear una forma SFML para la bola
    sf::CircleShape bola(formaBola.m_radius);
    bola.setFillColor(sf::Color::Red); // Color rojo para la bola

    // Crear la "línea invisible" debajo de la plataforma más baja
    b2BodyDef lineaInvisibleDef;
    lineaInvisibleDef.position.Set(0.0f, 50.0f); // Ubicación debajo de la plataforma más baja
    b2Body* lineaInvisible = mundo.CreateBody(&lineaInvisibleDef);

    // Crear una forma rectangular muy delgada para la línea invisible
    b2PolygonShape formaLineaInvisible;
    formaLineaInvisible.SetAsBox(800.0f / 2.0f, 1.0f); // Ancho completo de la pantalla y muy delgada
    b2FixtureDef fixtureLineaInvisibleDef;
    fixtureLineaInvisibleDef.shape = &formaLineaInvisible;
    lineaInvisible->CreateFixture(&fixtureLineaInvisibleDef);

    // Bucle principal del juego
    while (ventana.isOpen())
    {
        // Procesar eventos
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }

        // Controlar la bola con las teclas
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(-fuerza, 0), cuerpoBola->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(fuerza, 0), cuerpoBola->GetWorldCenter(), true);
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && puedeSaltar)
        {
            cuerpoBola->ApplyLinearImpulse(b2Vec2(0, -20.0f), cuerpoBola->GetWorldCenter(), true); // Aumentamos la fuerza del salto
            puedeSaltar = false;
        }

        // Verificar si la bola está tocando una plataforma para permitir el salto
        puedeSaltar = false;
        for (const auto& plataforma : plataformas)
        {
            for (b2ContactEdge* ce = cuerpoBola->GetContactList(); ce; ce = ce->next)
            {
                if (ce->contact->GetFixtureA()->GetBody() == plataforma || ce->contact->GetFixtureB()->GetBody() == plataforma)
                {
                    puedeSaltar = true;
                    break;
                }
            }
        }

        // Verificar si la bola toca la línea invisible debajo de la plataforma más baja
        if (cuerpoBola->GetPosition().y > 600.0f) // Si la bola cae debajo de la pantalla
        {
            cuerpoBola->SetTransform(b2Vec2(200.0f, 400.0f), 0); // Reposicionar bola
            cuerpoBola->SetLinearVelocity(b2Vec2(0, 0)); // Detener la bola
            cuerpoBola->SetAngularVelocity(0);
        }

        // Actualizar el mundo de Box2D
        mundo.Step(1.0f / 60.0f, 6, 2);

        // Actualizar la posición de la cámara para que siga la bola
        b2Vec2 posicionBola = cuerpoBola->GetPosition();
        camara.setCenter(posicionBola.x, posicionBola.y);

        // Aplicar la cámara
        ventana.setView(camara);

        // Limpiar la ventana
        ventana.clear();

        // Dibujar las plataformas
        for (size_t i = 0; i < formasPlataformas.size(); ++i)
        {
            formasPlataformas[i].setPosition(
                plataformas[i]->GetPosition().x,
                plataformas[i]->GetPosition().y);
            ventana.draw(formasPlataformas[i]);
        }

        // Dibujar la bola
        bola.setPosition(cuerpoBola->GetPosition().x, cuerpoBola->GetPosition().y);
        ventana.draw(bola);

        // Mostrar la ventana
        ventana.display();
    }

    return 0;
}
