#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../Body/RigidBody.h"
#include"../Body/ContactMechanic.h"
#include<string>
class Rect : public RigidBody , public ContactMech {
	std::shared_ptr<sf::RectangleShape> shape;
	sf::Font font;
	sf::Text text;
	float DT;
public:
	Rect() = default;
	Rect(const int id ,const sf::Vector2f& pos, const sf::Vector2f& size);
public:
	void Load();
	void Update(const float& dt);
	void CollisionUpdate( sf::RectangleShape& R2, RigidBody& F2 , ContactMech& contact);
	void Draw(std::shared_ptr<sf::RenderWindow>window);


private:
	void ReCentered();
	void MovementUpdate();
	inline void DisplayPositionAndVelocity();
	inline void FindMaxVelocities() override;
	inline sf::Vector2f& NewPosition(const float& dt) override;
};

