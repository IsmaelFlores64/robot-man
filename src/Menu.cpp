#include "Menu.hpp"

Menu::Menu()
{
    // Cargar fuente
    if (!font.loadFromFile("assets/fonts/Robotica.ttf"))
    {
        throw std::runtime_error("Error al cargar la fuente");
    }

    // Cargar música
    if (!music.openFromFile("assets/music/Menu.ogg"))
    {
        throw std::runtime_error("Error al cargar la música");
    }
    music.setLoop(true);

    // Cargar imagen de fondo
    if (!backgroundTexture.loadFromFile("assets/images/Robotman2.jpg"))
    {
        throw std::runtime_error("Error al cargar la imagen de fondo");
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Inicializar opciones del menú
    options = {"JUGAR", "CONTROLES", "SALIR"};
    for (size_t i = 0; i < options.size(); ++i)
    {
        sf::Text text(options[i], font, 40);
        text.setPosition(300, 200 + i * 50);
        text.setFillColor(sf::Color::White);
        menuTexts.push_back(text);
    }
    selectedOption = 0;
    menuTexts[selectedOption].setFillColor(sf::Color::Red);
}

void Menu::playMusic()
{
    music.play();
}

int Menu::handleInput(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                menuTexts[selectedOption].setFillColor(sf::Color::White);
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
                menuTexts[selectedOption].setFillColor(sf::Color::Red);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                menuTexts[selectedOption].setFillColor(sf::Color::White);
                selectedOption = (selectedOption + 1) % options.size();
                menuTexts[selectedOption].setFillColor(sf::Color::Red);
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {
                if (options[selectedOption] == "JUGAR")
                {
                    return 1; // Iniciar el juego
                }
                else if (options[selectedOption] == "CONTROLES")
                {
                    mostrarConfiguracion(window);
                }
                else if (options[selectedOption] == "SALIR")
                {
                    window.close();
                }
            }
        }
    }
    return 0; // Continuar en el menú
}

void Menu::draw(sf::RenderWindow &window)
{
    window.draw(backgroundSprite);
    for (const auto &text : menuTexts)
    {
        window.draw(text);
    }
}

void Menu::mostrarConfiguracion(sf::RenderWindow &window)
{
    sf::Text title("CONTROLES", font, 50);
    title.setPosition(200, 50);
    title.setFillColor(sf::Color::Yellow);

    sf::Text details(
        "- Flechas Arriba/Abajo: Moverse por el menu\n"
        "- Enter: Seleccionar una opcion\n"
        "- Flechas Izquierda/Derecha: Mover personaje\n"
        "- Barra Espaciadora: Disparar\n"
        "- Flecha Arriba (en el juego): Saltar\n"
        "- Escape: Regresar al menu principal",
        font, 20);
    details.setPosition(100, 150);
    details.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                return;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(details);
        window.display();
    }
}
