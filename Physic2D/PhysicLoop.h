#pragma once
#include<SFML/Graphics.hpp>
#include<memory>
#include<iostream>
#include"Objects/Rect.h"
class PhysicLoop{
private:
	std::shared_ptr<sf::RenderWindow>window;
	sf::Event event;
	sf::Clock clock;
	float DT;

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
private:
	void Deltatime();

};

