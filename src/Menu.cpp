#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

int main() {
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Menu de Inicio");

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
                        // Aquí iría el código para iniciar el juego
                        
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
