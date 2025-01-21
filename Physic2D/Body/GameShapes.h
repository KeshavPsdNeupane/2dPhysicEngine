#pragma once
#include"RigidBody.h"
#include<SFML/Graphics.hpp>
#include"ContactMechanic.h"

class GameShape : public RigidBody {
public:
	std::shared_ptr<sf::RectangleShape> shape;
public:
	GameShape() = default;
	GameShape(const int& id, const float& mass, const sf::Vector2f& position, const sf::Vector2f& size,
		const sf::Vector2f& velocity, const sf::Vector2f& acceleration,
		const sf::Vector2f& coefficientOfRestitution, const sf::Vector2f& ceofficientOfFriction)
		:
		shape(std::make_shared<sf::RectangleShape>()),
		RigidBody(id, mass, position, size, velocity,
			acceleration, coefficientOfRestitution, ceofficientOfFriction) {}

public:
	virtual void Load() = 0;
	virtual void Update(const float& dt) = 0;
	virtual void CollisionRedirection(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape, ContactMech& contact) = 0;
	virtual void Draw(std::shared_ptr<sf::RenderWindow>window) = 0;
};