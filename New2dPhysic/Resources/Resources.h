#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
class Resources{
	sf::Font font;
public:
	Resources();
	sf::Font& GetFont() { return font; }
};

