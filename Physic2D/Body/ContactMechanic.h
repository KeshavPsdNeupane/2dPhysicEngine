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
	void PlayerCollisionDetection(sf::RectangleShape& R1, RigidBody& F1,
		sf::RectangleShape& R2, RigidBody& F2, ContactMech& contact);
	void PLayerCollisionWIthShape(std::shared_ptr<GameShape> playerShape ,
		std::shared_ptr<GameShape> otherShape , ContactMech& contact);

	void PathCollsionHandleWithShape(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape);



	virtual void PathBasedCollisionHandle(sf::FloatRect& Bound1, RigidBody& F1,
		sf::FloatRect& Bound2, RigidBody& F2);



	// FRICTION
	void Friction(sf::RectangleShape& R1, RigidBody& F1,
		sf::RectangleShape& R2, RigidBody& F2, const float& dt);

	// THIS IS PREVIOUS IMPLEMENTATION OF COLLISION DETECTION SO JUST KEEPING THIS FOR LEGACY 
	void CollisionDetection(sf::RectangleShape& R1, RigidBody& F1,
		sf::RectangleShape& R2, RigidBody& F2);

protected:
	bool AABBIntersect(std::shared_ptr<GameShape> playerShape, std::shared_ptr<GameShape> otherShape);
	void ResetForNewCollision();
	inline void DirectionFinder();
	void PenetrationResoluter(RigidBody& F1, RigidBody& F2);
	void EffectiveEFinder(RigidBody& F1, RigidBody& F2);
	inline void CollisionThreshold();
};

