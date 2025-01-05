#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../Body/GameShapes.h"
#include"../Body/ContactMechanic.h"
#include<string>

class Rect : public GameShape  {
	struct GameClock{
		sf::Clock jumpClock;
	}Gclock;

	sf::Font font;
	sf::Text text;
	sf::CircleShape circle;
	float DT;
	int points;
	bool isLarge;
public:
	Rect() = default;
	Rect(const int id , const int colid, const float mass , const sf::Vector2f pos,
		const sf::Vector2f size,const sf::Vector2f coeffOfRest , 
		const sf::Vector2f coeffOfFriction);
public:
	inline void SetPosition(const sf::Vector2f position)override;
	inline void SetSize(const sf::Vector2f size)override;
	inline sf::CircleShape& GetCircle() { return this->circle; }
	inline void SetPoints(const int points) { this->points = points; }
	inline int GetPoints() const { return this->points; }
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
