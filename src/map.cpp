#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

int main() {
    // Ruta de la imagen
    std::string imagePath = "Microscheme.png";

    // Verificar si el archivo existe antes de cargar
    if (!std::filesystem::exists(imagePath)) {
        std::cerr << "Error: El archivo '" << imagePath << "' no existe en el directorio actual." << std::endl;
        return -1;
    }

    // Cargar la imagen
    sf::Image image;
    if (!image.loadFromFile(imagePath)) {
        std::cerr << "Error: No se pudo cargar la imagen." << std::endl;
        return -1;
    }

    // ... resto del código
}
