#include <SFML/Graphics.hpp>

// Enumeración para representar las diferentes acciones
enum class EnemigosAction { Idle, Move };

int main()
{
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Animado");

    // Cargar el spritesheet desde un archivo
    sf::Texture texture;
    if (!texture.loadFromFile("assets/images/Retro-Lines-Enemies alacran.png"))
    {
        // Manejo de error si no se puede cargar la imagen
        return -1;
    }

    // Crear un sprite y asignarle la textura
    sf::Sprite sprite(texture);
    sprite.setPosition(400, 300);

    // Escalar el sprite para hacerlo más grande
    sprite.setScale(5.0f, 5.0f); // Ampliar a un tamaño mínimo de 80 píxeles

    // Parámetros del spritesheet
    const int frameWidth = 16;  // Ancho de cada frame
    const int frameHeight = 32; // Alto de cada frame
    const int numFramesPerAction = 6; // Número de frames por acción

    // Variables para controlar la animación
    sf::Clock clock;
    float frameTime = 0.2f; // Tiempo entre cada frame en segundos
    int currentFrame = 0;

    // Acción actual del enemigo
    EnemigosAction currentAction = EnemigosAction::Idle;

    while (window.isOpen())
    {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Cambiar de acción con las teclas
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                    currentAction = EnemigosAction::Idle;
                else if (event.key.code == sf::Keyboard::Num2)
                    currentAction = EnemigosAction::Move;
            }
        }

        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % numFramesPerAction;

            // Determinar la fila correspondiente a la acción
            int row = 0; // Solo usar fila 0 para Idle (cuadro naranja)

            // Establecer el rectángulo de textura del sprite
            if (currentAction == EnemigosAction::Idle)
            {
                row = 0; // Fila de la acción "Idle" (cuadro naranja)
            }

            sprite.setTextureRect(sf::IntRect(
                currentFrame * frameWidth, // X del frame
                row * frameHeight,        // Y del frame
                frameWidth,               // Ancho del frame
                frameHeight               // Alto del frame
            ));

            clock.restart();
        }

        // Dibujar en la ventana
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}