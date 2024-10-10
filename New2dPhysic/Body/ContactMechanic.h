#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include"RigidBody.h"
class GameShape;
class ContactMech {
protected:
	sf::FloatRect B1;
	sf::FloatRect B2;
	sf::Vector2f resolution;
	sf::Vector2f u1;
	sf::Vector2f u2;
	sf::Vector2f Vrelative;
	sf::Vector2f Vunit;
	sf::Vector2f v1;
	sf::Vector2f v2;
	sf::Vector2f e;
	sf::Vector2f accleration;
	sf::Vector2f coeffOfFriction;
	float horizontalOverlap;
	float verticalOverlap;
	float eEffective;
	float M1;
	float M2;
	float gravity;
	float frictionDeceleratedVelocity;
public:
	ContactMech();
public:
	void CollsionDetection(std::shared_ptr<GameShape> playerShape ,
		std::shared_ptr<GameShape> otherShape , ContactMech& contact);

	void HeavyObjectCollisionHandle(std::shared_ptr<GameShape> playerShape,
		GameShape& otherShape);

	void LightObjectCollisionHandle(std::shared_ptr<GameShape> playerShape,
		GameShape& otherShape);


	// FRICTION
	void ApplyFriction(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape, const float& dt);

protected:
	void ResetForNewCollision();
	inline void DirectionFinder();
	void PenetrationResoluter(RigidBody& F1, RigidBody& F2);
	void EffectiveEFinder(RigidBody& F1, RigidBody& F2);
	inline void CollisionThreshold();
};

