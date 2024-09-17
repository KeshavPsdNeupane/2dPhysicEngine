#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../Body/RigidBody.h"
class Rect{
	int id;
	RigidBody frame;
	sf::RectangleShape shape;
	float DT;
	sf::Vector2f gravity;
public:
	Rect() = default;
	Rect(const sf::Vector2f& pos, const sf::Vector2f& size);

public:
	void Load();
	void Update(const float& dt);
	void Draw(std::shared_ptr<sf::RenderWindow>window);


private:
	void ReCentered();
};

