#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<array>
class Resources {
	sf::Font font;
	std::array<sf::Color, 17> color;
public:
	Resources();
	sf::Font& GetFont() { return font; }
	sf::Color& GetColor(int i) { return color[i]; }
};

