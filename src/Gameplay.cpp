#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int fuerza = 1;
    float frameTime = 0.1f;
    float acumuladorTiempo = 0.0f;
    int frameActual = 0;
    int numFramesMovimiento = 6;
    float tiempoEntreDisparos = 0.5f;
    float tiempoDesdeUltimoDisparo = 0.0f;
    bool puedeSaltar = true;

    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Ejemplo de Física con Box2D y SFML");

    sf::View camara(sf::FloatRect(0, 0, 800, 600));

    b2Vec2 vectorGravedad(0.0f, 10.0f);
    b2World mundo(vectorGravedad);

    b2BodyDef cuerpoSueloDef;
    cuerpoSueloDef.position.Set(400, 500.0f); // Posición del centro del cuerpo
    b2Body *cuerpoSuelo = mundo.CreateBody(&cuerpoSueloDef);

    // Crear una forma rectangular
    b2PolygonShape formaSuelo;
    int boxWidth = 600; // 600 pixeles de ancho
    int boxHeight = 10; // 10 pixeles de alto
    formaSuelo.SetAsBox(boxWidth / 2.0f, boxHeight / 2.0f);

    // Agregar la forma al cuerpo
    b2FixtureDef fixtureSueloDef;
    fixtureSueloDef.shape = &formaSuelo;
    fixtureSueloDef.friction = 1.0f;
    cuerpoSuelo->CreateFixture(&fixtureSueloDef);

    // Crear un cuerpo dinámico
    b2BodyDef cuerpoBolaDef;
    cuerpoBolaDef.type = b2_dynamicBody;
    cuerpoBolaDef.position.Set(400.0f, 300.0f);
    b2Body *cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);

    // Crear una forma rectangular para colisión (hitbox ajustada a 10 de ancho)
    b2PolygonShape formaBola;
    formaBola.SetAsBox(5.0f, 50.0f); // Dimensiones del personaje (ancho 10, alto 100)

    // Agregar la forma al cuerpo
    b2FixtureDef fixtureBolaDef;
    fixtureBolaDef.shape = &formaBola;
    fixtureBolaDef.density = 0.01f;
    fixtureBolaDef.friction = 0.7f;
    fixtureBolaDef.restitution = 0.1f; // Elasticidad
    cuerpoBola->CreateFixture(&fixtureBolaDef);

    // Cargar la textura de la hoja de sprites
    sf::Texture texturaBola;
    if (!texturaBola.loadFromFile("assets/images/Robot.png"))
    {
        cerr << "Error al cargar la textura de la hoja de sprites." << endl;
        return -1;
    }

    // Crear el sprite para la bola
    sf::Sprite spriteBola;
    spriteBola.setTexture(texturaBola);

    // Configurar las dimensiones de los fotogramas
    int spriteWidth = texturaBola.getSize().x / numFramesMovimiento; // Ancho de un fotograma
    int spriteHeight = texturaBola.getSize().y;                      // Alto de un fotograma

    // Configurar el rectángulo inicial del sprite (primer fotograma)
    spriteBola.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));
    spriteBola.setOrigin(spriteWidth / 2.0f, spriteHeight - 10.0f); // Ajustar los pies al suelo

    // Vector para almacenar balas
    struct Bala
    {
        sf::CircleShape shape;
        bool moviendoDerecha;
    };
    std::vector<Bala> balas;

    // Bucle principal del juego
    sf::Clock reloj;            // Reloj para medir el tiempo entre fotogramas
    bool mirandoDerecha = true; // Para determinar la dirección del personaje

    while (ventana.isOpen())
    {
        // Procesar eventos
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }

        // Variables de control de estado
        bool estaMoviendose = false;

        // Controlar la bola con el teclado
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            cuerpoBola->SetLinearVelocity(b2Vec2(-fuerza * 10, cuerpoBola->GetLinearVelocity().y));
            mirandoDerecha = false;
            estaMoviendose = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            cuerpoBola->SetLinearVelocity(b2Vec2(fuerza * 10, cuerpoBola->GetLinearVelocity().y));
            mirandoDerecha = true;
            estaMoviendose = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && puedeSaltar)
        {
            cuerpoBola->SetLinearVelocity(b2Vec2(cuerpoBola->GetLinearVelocity().x, -40.0f)); // Salto más fuerte
            puedeSaltar = false;
        }

        // Restablecer el salto al tocar el suelo
        if (cuerpoBola->GetLinearVelocity().y == 0)
        {
            puedeSaltar = true;
        }

        // Actualizar el tiempo desde el último disparo
        tiempoDesdeUltimoDisparo += reloj.restart().asSeconds();

        // Disparar una bala cuando se presiona la tecla Espacio
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && tiempoDesdeUltimoDisparo >= tiempoEntreDisparos)
        {
            sf::CircleShape bala(5.0f); // Crear una bolita con radio de 5 píxeles
            bala.setFillColor(sf::Color::Red);
            bala.setPosition(spriteBola.getPosition());
            balas.push_back({bala, mirandoDerecha});
            tiempoDesdeUltimoDisparo = 0.0f; // Reiniciar el temporizador de disparos
        }

        // Actualizar el mundo de Box2D
        mundo.Step(1.0f / 60.0f, 6, 2);

        // Actualizar posición de la cámara
        b2Vec2 posicionBola = cuerpoBola->GetPosition();
        camara.setCenter(posicionBola.x, posicionBola.y);
        ventana.setView(camara);

        // Actualizar la animación del sprite
        acumuladorTiempo += reloj.restart().asSeconds();
        if (estaMoviendose)
        {
            if (acumuladorTiempo >= frameTime)
            {
                acumuladorTiempo -= frameTime;
                frameActual = (frameActual + 1) % numFramesMovimiento;
                spriteBola.setTextureRect(sf::IntRect(frameActual * spriteWidth, 0, spriteWidth, spriteHeight));
            }
        }
        else
        {
            spriteBola.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));
        }

        // Actualizar la dirección del sprite
        spriteBola.setScale(mirandoDerecha ? 1.0f : -1.0f, 1.0f);

        // Actualizar la posición del sprite
        spriteBola.setPosition(posicionBola.x, posicionBola.y);

        // Mover las balas
        for (auto &bala : balas)
        {
            if (bala.moviendoDerecha)
            {
                bala.shape.move(1.0f, 0); // Velocidad de la bala reducida a 1
            }
            else
            {
                bala.shape.move(-1.0f, 0); // Velocidad de la bala reducida a 1
            }
        }

        // Limpiar la ventana
        ventana.clear();

        // Dibujar el suelo
        sf::RectangleShape suelo(sf::Vector2f(boxWidth, boxHeight));
        suelo.setOrigin(boxWidth / 2.0f, boxHeight / 2.0f);
        suelo.setPosition(cuerpoSuelo->GetPosition().x, cuerpoSuelo->GetPosition().y);
        ventana.draw(suelo);

        // Dibujar el sprite animado
        ventana.draw(spriteBola);

        // Dibujar las balas
        for (auto &bala : balas)
        {
            ventana.draw(bala.shape);
        }

        // Mostrar la ventana
        ventana.display();
    }

    return 0;
}
