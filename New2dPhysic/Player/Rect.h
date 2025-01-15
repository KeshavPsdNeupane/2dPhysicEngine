#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../Body/GameShapes.h"
#include"../Body/ContactMechanic.h"
#include<string>



class Rect : public GameShape  {

	struct GameClock{
		sf::Clock jumpClock;
	}gameClock;

	struct Bools {
	}bools;

	struct MaxTimeConstraints {
		float JUMP_TIME_CONSTRAINTS = 0.0f;
	}TimeConstraints;

	struct ForceApplication {
		// this shits r applied to a object with mass 60 kg 
		//so make your mapping yourself with other thingys
		float MOVEMENT_FORCE = 35775.0f;
		float JUMP_FORCE = 250.0f;  // this thingy is adding velocity not accleration
	}ApplyMotionForce;

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
		const sf::Vector2f coeffOfFriction ,const sf::Font& font);
	~Rect();

public:
	inline void SetPosition(const sf::Vector2f position)override;
	inline void SetSize(const sf::Vector2f size)override;
	inline int GetPoints() const { return this->points; }
	const inline void SetPoints(const int points) { this->points = points; }

public:
	void Load(std::shared_ptr<Engine::ResourceManager> resources) override;
	void Update(const float& dt) override;
	void Draw(std::shared_ptr<sf::RenderWindow>window) override;
	void DisplayPositionAndVelocity();
	void ReCentered();


	void ShowVel() {std::cout << " velocity = " << this->velocity.x << " " << this->velocity.y << "\n\n";}

private:
	void MovementUpdate();
	void ApplyGravity() { this->acceleration.y = GMNumber::GRAVITY; }
	inline void FindMaxVelocities() override;
	inline sf::Vector2f& NewPosition(const float& dt) override;

	void JumpUpdate();

	void JumpTimeConstraintsFinder();
};
