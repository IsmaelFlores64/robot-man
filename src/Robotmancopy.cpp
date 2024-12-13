#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
using namespace std;

// --- Función para mostrar la configuración de controles ---
void mostrarConfiguracion(sf::RenderWindow &ventana, const sf::Font &font)
{
    sf::Text titulo("CONTROLES", font, 50);
    titulo.setPosition(200, 50);
    titulo.setFillColor(sf::Color::Yellow);

    sf::Text detalles(
        "- Flechas Arriba/Abajo: Moverse por el menu\n"
        "- Enter: Seleccionar una opcion\n"
        "- Flechas Izquierda/Derecha: Mover personaje\n"
        "- Barra Espaciadora: Disparar\n"
        "- Flecha Arriba (en el juego): Saltar\n"
        "- Escape: Regresar al menu principal",
        font, 20);
    detalles.setPosition(100, 150);
    detalles.setFillColor(sf::Color::White);

    while (ventana.isOpen())
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
            {
                ventana.close();
            }
            if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape)
            {
                return;
            }
        }

        ventana.clear(sf::Color::Black);
        ventana.draw(titulo);
        ventana.draw(detalles);
        ventana.display();
    }
}

// --- Función para actualizar animaciones ---
void actualizarAnimacion(
    float frameTime,
    float &acumuladorTiempo,
    int &frameActual,
    sf::Sprite &sprite,
    int numFrames,
    int spriteWidth,
    int spriteHeight,
    bool estaMoviendose)
{
    if (estaMoviendose)
    {
        acumuladorTiempo += frameTime;
        if (acumuladorTiempo >= frameTime)
        {
            acumuladorTiempo -= frameTime;
            frameActual = (frameActual + 1) % numFrames;
            sprite.setTextureRect(sf::IntRect(frameActual * spriteWidth, 0, spriteWidth, spriteHeight));
        }
    }
    else
    {
        sprite.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));
    }
}

// --- Función para iniciar el juego ---
void iniciarJuego(sf::RenderWindow &ventana)
{
    const int VENTANA_ANCHO = 800;
    const int VENTANA_ALTO = 600;
    float frameTime = 0.1f;
    float acumuladorTiempo = 0.0f;
    int frameActual = 0;
    int numFramesMovimiento = 6;

    // Mundo físico de Box2D
    b2Vec2 gravedad(0.0f, 10.0f);
    b2World mundo(gravedad);

    // Cargar la textura del personaje
    sf::Texture texturaBola;
    if (!texturaBola.loadFromFile("assets/images/Robot.png"))
    {
        cerr << "Error al cargar la textura." << endl;
        return;
    }
    sf::Sprite spriteBola(texturaBola);
    int spriteWidth = texturaBola.getSize().x / numFramesMovimiento;
    int spriteHeight = texturaBola.getSize().y;
    spriteBola.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));
    spriteBola.setOrigin(spriteWidth / 2.0f, spriteHeight - 10.0f);

    struct Bala
    {
        sf::CircleShape shape;
        bool moviendoDerecha;
    };
    std::vector<Bala> balas;

    bool mirandoDerecha = true;

    while (ventana.isOpen())
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
            {
                ventana.close();
            }
        }

        // Control de movimiento
        bool estaMoviendose = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            mirandoDerecha = false;
            estaMoviendose = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            mirandoDerecha = true;
            estaMoviendose = true;
        }

        // Actualizar la animación
        actualizarAnimacion(frameTime, acumuladorTiempo, frameActual, spriteBola, numFramesMovimiento, spriteWidth, spriteHeight, estaMoviendose);

        // Mover balas
        for (auto &bala : balas)
        {
            bala.shape.move(bala.moviendoDerecha ? 5.0f : -5.0f, 0);
        }

        // Eliminar balas fuera de pantalla
        balas.erase(
            std::remove_if(balas.begin(), balas.end(), [VENTANA_ANCHO](const Bala &bala)
                           { return bala.shape.getPosition().x < 0 || bala.shape.getPosition().x > VENTANA_ANCHO; }),
            balas.end());

        // Dibujar escena
        ventana.clear();
        ventana.draw(spriteBola);
        for (const auto &bala : balas)
        {
            ventana.draw(bala.shape);
        }
        ventana.display();
    }
}

int main()
{
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Menu de Inicio");

    // Cargar fuente
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Robotica.ttf"))
    {
        cerr << "Error al cargar la fuente" << endl;
        return -1;
    }

    // Cargar música
    sf::Music music;
    if (!music.openFromFile("assets/music/Menu.ogg"))
    {
        cerr << "Error al cargar la música" << endl;
        return -1;
    }
    music.setLoop(true);
    music.play();

    // Cargar imagen de fondo
    sf::Texture texturaFondo;
    if (!texturaFondo.loadFromFile("assets/images/Robotman3.jpg"))
    {
        cerr << "Error al cargar la imagen de fondo" << endl;
        return -1;
    }
    sf::Sprite spriteFondo(texturaFondo);

    // Opciones del menú
    std::vector<std::string> opciones = {"JUGAR", "CONTROLES", "SALIR"};
    std::vector<sf::Text> textosMenu;

    for (size_t i = 0; i < opciones.size(); ++i)
    {
        sf::Text text(opciones[i], font, 40);
        text.setPosition(300, 200 + i * 50);
        text.setFillColor(sf::Color::White);
        textosMenu.push_back(text);
    }

    int opcionSeleccionada = 0;
    textosMenu[opcionSeleccionada].setFillColor(sf::Color::Red);

    while (ventana.isOpen())
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
            {
                ventana.close();
            }
            if (evento.type == sf::Event::KeyPressed)
            {
                if (evento.key.code == sf::Keyboard::Up)
                {
                    textosMenu[opcionSeleccionada].setFillColor(sf::Color::White);
                    opcionSeleccionada = (opcionSeleccionada - 1 + opciones.size()) % opciones.size();
                    textosMenu[opcionSeleccionada].setFillColor(sf::Color::Red);
                }
                else if (evento.key.code == sf::Keyboard::Down)
                {
                    textosMenu[opcionSeleccionada].setFillColor(sf::Color::White);
                    opcionSeleccionada = (opcionSeleccionada + 1) % opciones.size();
                    textosMenu[opcionSeleccionada].setFillColor(sf::Color::Red);
                }
                else if (evento.key.code == sf::Keyboard::Enter)
                {
                    if (opciones[opcionSeleccionada] == "JUGAR")
                    {
                        iniciarJuego(ventana);
                    }
                    else if (opciones[opcionSeleccionada] == "CONTROLES")
                    {
                        mostrarConfiguracion(ventana, font);
                    }
                    else if (opciones[opcionSeleccionada] == "SALIR")
                    {
                        ventana.close();
                    }
                }
            }
        }

        ventana.clear(sf::Color::Black);
        ventana.draw(spriteFondo);
        for (const auto &texto : textosMenu)
        {
            ventana.draw(texto);
        }
        ventana.display();
    }

    return 0;
}
