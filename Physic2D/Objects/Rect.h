#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../Body/RigidBody.h"
#include"../Body/ContactMechanic.h"
#include<string>
class Rect{
	ContactMech contact;
	RigidBody frame;
	sf::RectangleShape shape;
	sf::Vector2f gravity;
	sf::Font font;
	sf::Text text;
	float DT;
public:
	Rect() = default;
	Rect(const int index ,const sf::Vector2f& pos, const sf::Vector2f& size);
public:
	inline void SetIndex(const float& index);
	inline void SetMass(const float& mass);
	inline void SetPosition(const sf::Vector2f& position );
	inline void SetVelocity(const sf::Vector2f& velocity);
	inline void SetAccleration(const sf::Vector2f& accleration);
	inline void SetCoefficientOfRestitution(const sf::Vector2f& E);
	inline void SetCoefficientOfFriction(const sf::Vector2f& u);


public:
	void Load();
	void Update(const float& dt);
	void Draw(std::shared_ptr<sf::RenderWindow>window);


private:
	void ReCentered();
	void MovementUpdate();
	inline void DisplayPositionAndVelocity();
};

