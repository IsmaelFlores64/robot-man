#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
// Menú    
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Menu de Inicio");

// Audio
    sf::Music music;
    if (!music.openFromFile("assets/music/Menu.ogg"))
    {
        // Error al cargar el archivo de música
        return -1;
    }
    // Reproducir la música
    music.play();

    // Cargar fuente
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Robotica.ttf")) {
        return -1; // Manejar error
    }

    // Opciones del menú
    std::vector<std::string> opciones = {
        "JUGAR",
        "CONFIGURACION",
        "CREDITOS",
        "SALIR"
    };

    // Crear objetos de texto para cada opción
    std::vector<sf::Text> textosMenu;
    for (size_t i = 0; i < opciones.size(); ++i) {
        sf::Text text(opciones[i], font, 40);
        text.setPosition(300, 200 + i * 50); // Separación vertical entre opciones
        text.setFillColor(sf::Color::White); // Color inicial
        textosMenu.push_back(text);
    }

    // Indicar cuál opción está seleccionada
    int opcionSeleccionada = 0;
    textosMenu[opcionSeleccionada].setFillColor(sf::Color::Red); // Resaltar la primera opción

    while (ventana.isOpen()) {

        // Manejar eventos
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }

            // Navegar entre opciones con las teclas
            if (evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::Up) {
                    textosMenu[opcionSeleccionada].setFillColor(sf::Color::White); // Desactivar el color anterior
                    opcionSeleccionada = (opcionSeleccionada - 1 + opciones.size()) % opciones.size();
                    textosMenu[opcionSeleccionada].setFillColor(sf::Color::Red); // Resaltar nueva opción
                }
                else if (evento.key.code == sf::Keyboard::Down) {
                    textosMenu[opcionSeleccionada].setFillColor(sf::Color::White);
                    opcionSeleccionada = (opcionSeleccionada + 1) % opciones.size();
                    textosMenu[opcionSeleccionada].setFillColor(sf::Color::Red);
                }

                // Seleccionar una opción con Enter
                if (evento.key.code == sf::Keyboard::Enter) {
                    if (opciones[opcionSeleccionada] == "JUGAR") {

// Juego ------------------------------------------------------------------------------------------
    int fuerza = 1;
    float frameTime = 0.1f; // Tiempo entre fotogramas de animación
    float acumuladorTiempo = 0.0f;
    int frameActual = 0;     // Fotograma actual de la animación
    int numFramesMovimiento = 6; // Número de fotogramas para la animación de movimiento

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

    // Crear una forma circular para colisión
    b2CircleShape formaBola;
    formaBola.m_radius = 25.0f;

    // Agregar la forma al cuerpo
    b2FixtureDef fixtureBolaDef;
    fixtureBolaDef.shape = &formaBola;
    fixtureBolaDef.density = 0.01f;
    fixtureBolaDef.friction = 0.7f;
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
    spriteBola.setOrigin(spriteWidth / 2.0f, spriteHeight); // Alinear la base del sprite con el suelo

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

        // Controlar la bola con el teclado
        bool estaMoviendose = false;
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            cuerpoBola->ApplyLinearImpulse(b2Vec2(0, -fuerza), cuerpoBola->GetWorldCenter(), true);
            estaMoviendose = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            cuerpoBola->ApplyLinearImpulse(b2Vec2(0, fuerza), cuerpoBola->GetWorldCenter(), true);
            estaMoviendose = true;
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
                        
                        ventana.close();
                    }
                    else if (opciones[opcionSeleccionada] == "SALIR") {
                        ventana.close();
                    }
                }
            }
        }

        // Dibujar el menú
        ventana.clear(sf::Color::Black);
        for (const auto& texto : textosMenu) {
            ventana.draw(texto);
        }
        ventana.display();
    }

    return 0;
}
