#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include"../Body/GameShapes.h"


struct PlayerReference {
	bool canjump = false;
	bool isInWater = false;
};

extern PlayerReference playerReference;



class Rect : public GameShape  {

	struct GameClock{
		sf::Clock jumpClock;
	}gameClock;

	struct Bools {
		bool canJump = false;
	}bools;

	struct MaxTimeConstraints {
		float JUMP_TIME_CONSTRAINTS = 0.0f;
	}TimeConstraints;

	struct ForceApplication {
		//THIS THINGY ADD VELOCITY NOT ACTUAL FORCE
		float MOVEMENT_FORCE = 150.0f;
		float JUMP_FORCE = 300.0f;  
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
		const float coeffOfFriction);
	~Rect();

public:
	inline void SetPosition(const sf::Vector2f position)override;
	inline void SetSize(const sf::Vector2f size)override;
	inline int GetPoints() const { return this->points; }
	const inline void SetPoints(const int points) { this->points = points; }
	Bools& GetBools() { return this->bools; }

public:
	void Load(std::shared_ptr<Engine::ResourceManager> resources) override;
	void Update(const float& dt) override;
	void Draw(std::shared_ptr<sf::RenderWindow>window) override;
	void DisplayPositionAndVelocity();
	void ReCentered();
	void DrawStats(std::shared_ptr<sf::RenderWindow>window);

private:
	void MovementUpdate();
	void ApplyGravity() { this->acceleration.y = GMNumber::GRAVITY; }
	inline void FindMaxVelocities() override;

	inline sf::Vector2f& NewPosition(const float& dt)override;

	void JumpUpdate();

	void JumpTimeConstraintsFinder();
};
