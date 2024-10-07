#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../Body/GameShapes.h"
#include"../Body/ContactMechanic.h"
#include<string>

class Rect : public GameShape , public ContactMech {
	sf::Font font;
	sf::Text text;
	float DT;

public:
	Rect() = default;
	Rect(const int id ,const sf::Vector2f& pos, const sf::Vector2f& size);
public:

	std::shared_ptr<sf::RectangleShape> GetShape() { return shape; }
	RigidBody& GetRigidBody() { return *this;}
	ContactMech& GetCollisionHandling() { return *this;}

public:
	void Load() override;
	void Update(const float& dt) override;
	void CollisionRedirection(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape,ContactMech& contact) override;
	void Draw(std::shared_ptr<sf::RenderWindow>window) override;

	void CollisionUpdate(sf::RectangleShape& R2, RigidBody& F2, ContactMech& contact);

private:
	void ReCentered();
	void MovementUpdate();
	inline void DisplayPositionAndVelocity();
	inline void FindMaxVelocities() override;
	inline sf::Vector2f& NewPosition(const float& dt) override;
};

