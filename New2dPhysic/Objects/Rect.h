#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../Body/GameShapes.h"
#include"../Body/ContactMechanic.h"
#include<string>

class Rect : public GameShape  {
	sf::Font font;
	sf::Text text;
	float DT;

public:
	Rect() = default;
	Rect(const int id , const int colid, const float mass , const sf::Vector2f pos, const sf::Vector2f size,
		const sf::Vector2f velocity , const sf::Vector2f accleration , const sf::Vector2f coeffOfRest , const sf::Vector2f coeffOfFriction);
public:
	std::shared_ptr<sf::RectangleShape> GetShape() const { return shape; }
	RigidBody& GetRigidBody()  { return *this;}
public:
	void Load() override;
	void Update(const float& dt) override;
	void Draw(std::shared_ptr<sf::RenderWindow>window) override;
	void DisplayPositionAndVelocity();
private:
	void ReCentered();
	void MovementUpdate();
	inline void FindMaxVelocities() override;
	//inline void Friction(std::shared_ptr<GameShape> other, ContactMech& contact);
	inline sf::Vector2f& NewPosition(const float& dt) override;
};

