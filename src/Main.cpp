#include <SFML/Graphics.hpp>
#include "Game.h"

void Update(float deltaTime);
void Render(sf::RenderWindow& window);

int main(){
    
    sf::Window window(sf::VideoMode(1200,900),"Megaman");
    sf::Clock deltaClock;

    Begin(window);
    while (window.isopen())
    {
        float deltaTima = deltaClock.restart().asSeconds();

        sf:: Event event{};
        while (window.pollEvent(event))
        {
            if (event.type = sf::Event::Closed)
            window.close();
        }

        Update(deltaTime);

        window.clear(); 
        Render(window);
        window.display();
        
    }
    
    return 0;

}
