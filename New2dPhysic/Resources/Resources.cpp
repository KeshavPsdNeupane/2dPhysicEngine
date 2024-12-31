#include "Resources.h"

Resources::Resources(){
	if (!this->font.loadFromFile("Asset/Fonts/arial.ttf")) {
		std::cerr << " unable to load font from Assect/Fonts/arial.ttf  " << std::endl;
	}
    this->color = {
    sf::Color::White,        // (255, 255, 255)
    sf::Color::Black,        // (0, 0, 0)
    sf::Color::Red,          // (255, 0, 0)
    sf::Color::Blue,         // (0, 0, 255)
    sf::Color::Green,        // (0, 255, 0)
    sf::Color::Yellow,       // (255, 255, 0)
    sf::Color::Cyan,         // (0, 255, 255)
    sf::Color::Magenta,      // (255, 0, 255)
    sf::Color(128, 128, 128), // Gray
    sf::Color(255, 165, 0),  // Orange
    sf::Color(128, 0, 128),  // Purple
    sf::Color(165, 42, 42),  // Brown
    sf::Color(255, 192, 203), // Pink
    sf::Color(0, 128, 128),  // Teal
    sf::Color(128, 128, 0),  // Olive
    sf::Color(0, 0, 128),    // Navy
    sf::Color::Transparent   // (0, 0, 0, 0)
    };
}
