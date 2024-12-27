#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../Body/GameShapes.h"
#include"../Body/ContactMechanic.h"
#include<string>

class Rect : public GameShape  {
	sf::Font font;
	sf::Text text;
	sf::Vector2f smallBallSize;
	sf::Vector2f largeBallSize;
	bool isBig;
	float DT;
public:
	Rect() = default;
	Rect(const int id , const int colid, const float mass , const sf::Vector2f pos, const sf::Vector2f size,
		const sf::Vector2f velocity , const sf::Vector2f accleration , const sf::Vector2f coeffOfRest , const sf::Vector2f coeffOfFriction);
public:
	sf::Vector2f& GetSmallBallSize() { return this->smallBallSize; }
	sf::Vector2f& GetLargeBallSize() { return this->largeBallSize; }
	void SetSmallBallSize(sf::Vector2f smallSize) { this->smallBallSize = smallSize; }
	void SetLargelBallSize(sf::Vector2f largeSize) { this->largeBallSize = largeSize; }

public:
	void Load() override;
	void Update(const float& dt) override;
	void Draw(std::shared_ptr<sf::RenderWindow>window) override;
	void DisplayPositionAndVelocity();
	void ReCentered();
private:
	void MovementUpdate();
	inline void FindMaxVelocities() override;
	inline sf::Vector2f& NewPosition(const float& dt) override;
};
