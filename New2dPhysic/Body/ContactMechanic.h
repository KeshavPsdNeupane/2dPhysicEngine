#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include"RigidBody.h"
#include"../World/WorldSuperClass.h"

class GameShape;
enum Direction {
	Right = 0,      
	Bottom = 1,      
	Left = 2,       
	Top = 3,       
};



class ContactMech {
protected:
	WorldSuperClass& world;

	sf::Vector2f resolution;
	sf::Vector2f u1;
	sf::Vector2f u2;
	sf::Vector2f Vunit;
	sf::Vector2f v1;
	sf::Vector2f v2;
	sf::Vector2f e;
	sf::Vector2f accleration;
	sf::Vector2f coeffOfFriction;
	float horizontalOverlap;
	float verticalOverlap;
	float M1;
	float M2;
	float gravity;
	float frictionDeceleratedVelocity;

public:
	ContactMech(WorldSuperClass& w);
public:
	void CollsionDetection(std::shared_ptr<GameShape> playerShape ,
		std::shared_ptr<GameShape> otherShape);
	
	// FRICTION
	void ApplyFriction(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape, const float& dt);


protected:
	bool CollisionBetweenCircleAndRectangle(sf::FloatRect& B1, sf::FloatRect& B2);
	void CollisionDetermination(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape);
	Direction HeavyObjectCollisionHandle(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape);
	void LightObjectCollisionHandle(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape);
	void InflatorCollisionHandle(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape);
	void DeflatorCollisionHandle(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape);

	void CollectableCollisionHandle(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape);
	void StaticEnemyCollisionHandle(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape);

	void CheckPointCollisionHandle(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape);

private:
	Direction CollisionDirectionFinder(std::shared_ptr<GameShape> playerShape,
		std::shared_ptr<GameShape> otherShape);
	void ResetForNewCollision();
	void PenetrationResoluter(GameShape& player , GameShape& other , Direction direction);
	void NewPenetrationResoluter(GameShape& player , GameShape& other, Direction direction);
	inline void EffectiveEFinder(RigidBody& F1, RigidBody& F2);
	inline void CollisionThreshold();
	void CalculateVelocity(float& v1, float& v2, float u1,
		float u2, float M1, float M2, float eEffective);


	//THIS FUNCTION RETURN SIGN OF THE NUMBER
	float Sign(float& num);
};

