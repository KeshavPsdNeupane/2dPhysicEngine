#pragma once
#include"RigidBody.h"
#include<SFML/Graphics.hpp>
#include"../Resources/ResourceManager.h"

class GameShape : public RigidBody {
protected:
	int id;
	short collisionId;
public:
	std::shared_ptr<sf::RectangleShape> shape;
public:
	GameShape() = default;
	GameShape(const int id , const int colId, const float mass, const sf::Vector2f position, const sf::Vector2f size,
		const sf::Vector2f velocity, const sf::Vector2f acceleration,
		const sf::Vector2f coefficientOfRestitution, const sf::Vector2f ceofficientOfFriction):
		shape(std::make_shared<sf::RectangleShape>()),
		id(id),
		collisionId(colId),
		RigidBody(mass, position, size, velocity,
			acceleration, coefficientOfRestitution, ceofficientOfFriction) {
		this->shape->setSize(size);
		this->shape->setPosition(position);
	}
	virtual ~GameShape() {}
public:
	const inline int GetShapeID() const { return this->id; }
	inline void SetShapeID(const int id) { this->id = id; }
	const inline int GetCollisionId() const { return this->collisionId; }
	inline void SetCollisionId(int collisionId) { this->collisionId = collisionId; }
public:
	virtual void Load(std::shared_ptr<Engine::ResourceManager> resources) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Draw(std::shared_ptr<sf::RenderWindow>window) = 0;
};