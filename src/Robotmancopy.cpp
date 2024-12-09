#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
using namespace std;

int main()
{
    int fuerza = 1;
    float frameTime = 0.1f; // Tiempo entre fotogramas de animación
    float acumuladorTiempo = 0.0f;
    int frameActual = 0;           // Fotograma actual de la animación
    int numFramesMovimiento = 6;   // Número de fotogramas para la animación de movimiento
    int numFramesSalto = 1;        // Número de fotogramas para la animación de salto
    int numFramesAgachado = 1;     // Número de fotogramas para la animación de agacharse
    int saltosDisponibles = 2;     // Máximo de 2 saltos consecutivos

    // Crear una ventana de SFML
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Ejemplo de Fisica con Box2D y SFML");

    //// Crear una vista (cámara)
    sf::View camara(sf::FloatRect(0, 0, 800, 600));

    // Crear un mundo de Box2D
    b2Vec2 vectorGravedad(0.0f, 10.0f);
    b2World mundo(vectorGravedad);

    // Crear un suelo estático
    b2BodyDef cuerpoSueloDef;
    cuerpoSueloDef.position.Set(400, 500.0f); // Posición del centro del cuerpo
    b2Body* cuerpoSuelo = mundo.CreateBody(&cuerpoSueloDef);

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
    b2Body* cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);

    // Crear una forma rectangular para colisión
    b2PolygonShape formaBola;
    formaBola.SetAsBox(25.0f, 50.0f); // Dimensiones del personaje (ancho, alto)

    // Agregar la forma al cuerpo
    b2FixtureDef fixtureBolaDef;
    fixtureBolaDef.shape = &formaBola;
    fixtureBolaDef.density = 0.01f;
    fixtureBolaDef.friction = 0.7f;
    fixtureBolaDef.restitution = 0.1f; // Elasticidad
    cuerpoBola->CreateFixture(&fixtureBolaDef);

    // Cargar la textura de la hoja de sprites
    sf::Texture texturaBola;
    if (!texturaBola.loadFromFile("assets/images/Robot.png")) {
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

    // Bucle principal del juego
    sf::Clock reloj; // Reloj para medir el tiempo entre fotogramas
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
        bool estaSaltando = false;
        bool estaAgachado = false;

        // Controlar la bola con el teclado
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            cuerpoBola->ApplyLinearImpulse(b2Vec2(-fuerza, 0), cuerpoBola->GetWorldCenter(), true);
            mirandoDerecha = false;
            estaMoviendose = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            cuerpoBola->ApplyLinearImpulse(b2Vec2(fuerza, 0), cuerpoBola->GetWorldCenter(), true);
            mirandoDerecha = true;
            estaMoviendose = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && saltosDisponibles > 0) {
            cuerpoBola->ApplyLinearImpulse(b2Vec2(0, -7), cuerpoBola->GetWorldCenter(), true);
            saltosDisponibles--;
            estaSaltando = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            estaAgachado = true;
        }

        // Restablecer los saltos cuando toca el suelo
        if (cuerpoBola->GetLinearVelocity().y == 0) {
            saltosDisponibles = 2;
        }

        // Actualizar el mundo de Box2D
        mundo.Step(1.0f / 60.0f, 6, 2);

        //// Actualizar la posición de la cámara para que siga la bola
        b2Vec2 posicionBola = cuerpoBola->GetPosition();
        camara.setCenter(posicionBola.x, posicionBola.y);

        //// Aplicar la cámara
        ventana.setView(camara);

        // Actualizar la animación del sprite
        acumuladorTiempo += reloj.restart().asSeconds();
        if (estaMoviendose) {
            if (acumuladorTiempo >= frameTime) {
                acumuladorTiempo -= frameTime;
                frameActual = (frameActual + 1) % numFramesMovimiento;
                spriteBola.setTextureRect(sf::IntRect(frameActual * spriteWidth, 0, spriteWidth, spriteHeight));
            }
        } else if (estaSaltando) {
            spriteBola.setTextureRect(sf::IntRect(numFramesMovimiento * spriteWidth, 0, spriteWidth, spriteHeight));
        } else if (estaAgachado) {
            spriteBola.setTextureRect(sf::IntRect((numFramesMovimiento + 1) * spriteWidth, 0, spriteWidth, spriteHeight));
        } else {
            // Estado de reposo: usar el primer fotograma
            spriteBola.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));
        }

        // Actualizar la dirección del sprite
        spriteBola.setScale(mirandoDerecha ? 1.0f : -1.0f, 1.0f);

        // Actualizar la posición del sprite
        spriteBola.setPosition(posicionBola.x, posicionBola.y);

        // Limpiar la ventana
        ventana.clear();

        // Dibujar el suelo
        sf::RectangleShape suelo(sf::Vector2f(boxWidth, boxHeight));
        suelo.setOrigin(boxWidth / 2.0f, boxHeight / 2.0f);
        suelo.setPosition(cuerpoSuelo->GetPosition().x, cuerpoSuelo->GetPosition().y);
        ventana.draw(suelo);

        // Dibujar el sprite animado
        ventana.draw(spriteBola);

        // Mostrar la ventana
        ventana.display();
    }

    return 0;
}
