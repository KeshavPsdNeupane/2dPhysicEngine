#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../Body/RigidBody.h"
#include"../Body/ContactMechanic.h"
#include<string>
class Rect : public RigidBody{
	ContactMech contact;
	//RigidBody frame;
	sf::RectangleShape shape;
	sf::Vector2f gravity;
	sf::Font font;
	sf::Text text;
	float DT;
public:
	Rect() = default;
	Rect(const int index ,const sf::Vector2f& pos, const sf::Vector2f& size);
public:
	void Load();
	void Update(const float& dt);
	void Draw(std::shared_ptr<sf::RenderWindow>window);


private:
	void ReCentered();
	void MovementUpdate();
	inline void DisplayPositionAndVelocity();
};

