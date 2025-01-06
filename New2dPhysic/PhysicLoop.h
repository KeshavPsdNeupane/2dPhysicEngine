#pragma once
#include<SFML/Graphics.hpp>
#include<memory>
#include<iostream>
#include"Body/ContactMechanic.h"
#include"GameGrid/GameGrid.h"
#include"string"

class PhysicLoop{
private:
	std::shared_ptr<sf::RenderWindow>window;
	sf::Event event;
	sf::Clock clock;
	ContactMech collisionAndFriction;
	GridResult updateDrawResultFromGrid;
	GridResult collisionResultFromGrid;
	sf::Text text;
	sf::Text text2;
	sf::Font font;
	float DT;
	int entityIdCounter;

public:
	PhysicLoop();

public:
	inline std::shared_ptr<sf::RenderWindow> GetWindow() { return window; }
	void RunPlysicLoop();
private:
	void SFMLEvent();
	void Load();
	void Update();
	void Draw();
	void DisplayStats();

private:
	void DeleteUnwanted();


};

