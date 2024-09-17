#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include"RigidBody.h"
class Collision {
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
	float horizontalOverlap;
	float verticalOverlap;
	float eEffective;
	float M1;
	float M2;

public: 
	Collision() = default;
	 void CollisionDetection(sf::RectangleShape& R1, RigidBody& F1,
		sf::RectangleShape& R2, RigidBody& F2);


private:
	void ResetForNewCollision();
	inline void DirectionFinder();
	void PenetrationResoluter(RigidBody& F1, RigidBody& F2);
	void EffectiveEFinder(RigidBody& F1, RigidBody& F2);
	inline void CollisionThreshold();
};

