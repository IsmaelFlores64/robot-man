#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>

class Enemigo
{
public:
    Enemigo(const std::string &textureFile, float speed, float verticalSpeed, int screenWidth, int screenHeight)
        : speed(speed), verticalSpeed(verticalSpeed), screenWidth(screenWidth), screenHeight(screenHeight), alive(true)
    {
        if (!texture.loadFromFile(textureFile))
        {
            throw std::runtime_error("Error al cargar la textura del enemigo");
        }
        sprite.setTexture(texture);
        sprite.setScale(2.0f, 2.0f);
        sprite.setPosition(screenWidth - 100, 50);
    }

    void update(float deltaTime)
    {
        if (!alive)
            return;

        sf::Vector2f position = sprite.getPosition();
        position.x -= speed * deltaTime;
        position.y += verticalSpeed * deltaTime;

        if (position.x + sprite.getGlobalBounds().width < 0)
        {
            position.x = static_cast<float>(screenWidth);
        }

        if (position.y + sprite.getGlobalBounds().height > screenHeight)
        {
            position.y = screenHeight - sprite.getGlobalBounds().height;
            alive = false;
        }

        sprite.setPosition(position);
    }

    void draw(sf::RenderWindow &window)
    {
        if (alive)
            window.draw(sprite);
    }

    bool checkCollision(const sf::CircleShape &bala)
    {
        return alive && sprite.getGlobalBounds().intersects(bala.getGlobalBounds());
    }

    void die()
    {
        alive = false;
    }

    bool isAlive() const
    {
        return alive;
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    float verticalSpeed;
    int screenWidth;
    int screenHeight;
    bool alive;
};

int main()
{
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Menu de Inicio");

    // Cargar fuente
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Robotica.ttf"))
    {
        std::cerr << "Error al cargar la fuente\n";
        return -1;
    }

    // Cargar música
    sf::Music music;
    if (!music.openFromFile("assets/music/Menu.ogg"))
    {
        std::cerr << "Error al cargar la música\n";
        return -1;
    }
    music.setLoop(true);
    music.play();

    // Cargar imagen de fondo
    sf::Texture texturaFondo;
    if (!texturaFondo.loadFromFile("assets/images/Robotman3.jpg"))
    {
        std::cerr << "Error al cargar la imagen de fondo\n";
        return -1;
    }

    sf::Sprite spriteFondo(texturaFondo);

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

    // Bucle para el menú
    while (ventana.isOpen())
    {
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                ventana.close();

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
                    if (opcionSeleccionada == 0) // JUGAR
                    {
                        ventana.close(); // Cerrar el menú y comenzar el juego
                    }
                    else if (opcionSeleccionada == 1) // CONTROLES
                    {
                        std::cout << "Controles: Usa las teclas de flecha para moverte.\n";
                    }
                    else if (opcionSeleccionada == 2) // SALIR
                    {
                        return 0; // Salir del programa
                    }
                }
            }
        }

        ventana.clear();
        ventana.draw(spriteFondo);

        for (const auto &texto : textosMenu)
        {
            ventana.draw(texto);
        }

        ventana.display();
    }

    // Comienza el juego después de cerrar el menú
    sf::RenderWindow ventanaJuego(sf::VideoMode(800, 600), "Juego");

    Enemigo enemigo("assets/images/blue_slime.png", 100.0f, 50.0f, 800, 600);

    sf::Texture texturaBola;
    if (!texturaBola.loadFromFile("assets/images/Robot.png"))
    {
        std::cerr << "Error al cargar la textura del personaje.\n";
        return -1;
    }

    sf::Sprite spriteBola(texturaBola);
    spriteBola.setOrigin(texturaBola.getSize().x / 2.0f, texturaBola.getSize().y / 2.0f);
    spriteBola.setPosition(100.0f, 500.0f);

    sf::Texture texturaFondoJuego;
    if (!texturaFondoJuego.loadFromFile("assets/images/Fondo.png"))
    {
        std::cerr << "Error al cargar la textura del fondo del juego.\n";
        return -1;
    }

    sf::Sprite fondoJuego(texturaFondoJuego);

    sf::RectangleShape piso(sf::Vector2f(800.0f, 20.0f));
    piso.setFillColor(sf::Color::Green);
    piso.setPosition(0.0f, 580.0f);

    std::vector<sf::CircleShape> balas;
    sf::Clock reloj;
    bool mirandoDerecha = true;

    while (ventanaJuego.isOpen())
    {
        sf::Event evento;
        while (ventanaJuego.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                ventanaJuego.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            spriteBola.move(-5.0f, 0);
            mirandoDerecha = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            spriteBola.move(5.0f, 0);
            mirandoDerecha = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            sf::CircleShape bala(5.0f);
            bala.setFillColor(sf::Color::Red);
            bala.setPosition(spriteBola.getPosition());
            balas.push_back(bala);
        }

        for (auto &bala : balas)
        {
            if (mirandoDerecha)
                bala.move(5.0f, 0);
            else
                bala.move(-5.0f, 0);
        }

        enemigo.update(reloj.restart().asSeconds());

        ventanaJuego.clear();
        ventanaJuego.draw(fondoJuego);
        ventanaJuego.draw(piso);
        enemigo.draw(ventanaJuego);
        ventanaJuego.draw(spriteBola);
        for (auto &bala : balas)
        {
            ventanaJuego.draw(bala);
        }

        ventanaJuego.display();
    }

    return 0;
}