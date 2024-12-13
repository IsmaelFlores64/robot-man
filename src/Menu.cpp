#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

// Mostrar configuración de controles
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
    if (!texturaFondo.loadFromFile("assets/images/Robotman2.jpg"))
    {
        std::cerr << "Error al cargar la imagen de fondo\n";
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
                        std::cout << "Inicia el juego...\n"; // Aquí iría el código del juego
                        ventana.close();
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

        ventana.clear();
        ventana.draw(spriteFondo); // Dibujar la imagen de fondo
        for (const auto &texto : textosMenu)
        {
            ventana.draw(texto);
        }
        ventana.display();
    }

    return 0;
}
