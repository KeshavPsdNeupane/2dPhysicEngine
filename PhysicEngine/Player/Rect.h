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
		sf::Clock movementAnimaton;
	}gameClock;

	struct Bools {
		bool canJump = false;
		bool isMovingRight = false;
		bool isMovingLeft = false;
	}bools;

	struct FrameCount {
		int movementFrameCount = 0;
	}frameCount;
	struct MaxFrameSize {
		int movementFrameSize = 4;
	}frameMaxSize;

	struct MaxTimeConstraints {
		float JUMP_TIME_CONSTRAINTS = 0.0f;
		float MOVEMENT_ANIMATION_TIME_CONSTRAINTS = 8 * 0.01666777f;
	}TimeConstraints;

	struct ForceApplication {
		//THIS THINGY ADD VELOCITY NOT ACTUAL FORCE
		float MOVEMENT_FORCE = 20.0f;
		float JUMP_FORCE = std::sqrt(2 * GMNumber::GRAVITY *(66.0f));  
	}ApplyMotionForce;

	sf::Font font;
	sf::Text text;
	sf::Texture texture;
	sf::Sprite sprite;
	float DT;
	float sizeOfSprite;
	//int points;
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
public:
	void Load(std::shared_ptr<Engine::ResourceManager> resources) override;
	void Update(const float& dt) override;
	void Draw(std::shared_ptr<sf::RenderWindow>window) override;
	void DisplayPositionAndVelocity();
	void ReCentered();
	void DrawStats(std::shared_ptr<sf::RenderWindow>window);

private:
	inline sf::Vector2f& NewPosition(const float& dt)override;
	void ApplyGravity() { this->acceleration.y = GMNumber::GRAVITY; }
	inline void FindMaxVelocities() override;

private:
	void MovementUpdate();
	void MOvementAnimation();
	void JumpUpdate();
	void JumpTimeConstraintsFinder();

};
