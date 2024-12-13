#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class Menu
{
private:
    sf::Font font;
    sf::Music music;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    std::vector<std::string> options;
    std::vector<sf::Text> menuTexts;
    size_t selectedOption;

public:
    Menu(); // Constructor
    void playMusic();
    int handleInput(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
    void mostrarConfiguracion(sf::RenderWindow &window);
};

#endif // MENU_HPP
