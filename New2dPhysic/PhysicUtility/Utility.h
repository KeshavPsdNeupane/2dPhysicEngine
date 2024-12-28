#pragma once
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>


namespace GMNumber {
	//  FOR WINDOWS 
	static constexpr float WINDOW_WIDTH = 800.0f;
	static constexpr float WINDOW_HEIGHT = 600.0f;
	static constexpr int MAX_FRAME_RATE = 60; ;

	// FOR ALL
	static constexpr float  ZERO = 0.0f;
	static constexpr float  UNIT = 1.0f;
	static constexpr float GRAVITY = 50.0f * 10.0f;// HERE 50 IS A MODIFIER AND 10 IS ACTUAL VALUE JUST LIKE IRL G OF 9.8 OR 10M/S

	// FOR RIGITBODY
	static constexpr float COEFF_MAX_VELOCITY_X = 9000.0f;
	static constexpr float COEFF_MAX_VELOCITY_Y = 1936.5f;
	static constexpr float ABSOLUTE_MAX_VELOCITY_X = 400.0f;
	static constexpr float ABSOLUTE_MAX_VELOCITY_Y = 800.0f;

	static constexpr float LOWEST_VELOCITY_THRESHOLD = 0.4f;
	static constexpr float MASS_THRESHOLD = 1000.0f;

	//FOR COEFF OF RESTITUTION
	static constexpr float COEFF_OF_RESTITUTION_OBJECT_X = 0.2f;
	static constexpr float COEFF_OF_RESTITUTION_OBJECT_Y = 0.3f;
	static constexpr float COEFF_OF_RESTITUTION_PATH_X = 0.7f;
	static constexpr float COEFF_OF_RESTITUTION_PATH_Y = 0.4f;


	//COLLISION THRESHOLD CALCULATION
	static constexpr float COLLISION_VELOCITY_THRESHOLD_X = GRAVITY * (1.0f/ MAX_FRAME_RATE)
		* (COEFF_OF_RESTITUTION_OBJECT_X + COEFF_OF_RESTITUTION_PATH_X)/4.0f;
	static constexpr float COLLISION_VELOCITY_THRESHOLD_Y = GRAVITY * (1.0f / MAX_FRAME_RATE)
		* (COEFF_OF_RESTITUTION_OBJECT_Y + COEFF_OF_RESTITUTION_PATH_Y + 0.1f) / 2.0f;


	// FOR COEFFICIENT OF FRICTION
	static constexpr float COEFF_OF_FRICTION_PATH = 0.5f;
	static constexpr float COEFF_OF_FRICTION_OBJECT = 0.0f;


	// RECT

	static constexpr float ABSOLUTE_ACCLERATION_FOR_PLAYER_X = 4000.0f;
	static constexpr float ABSOLUTE_ACCLERATION_FOR_PLAYER_Y = 800.0f;
	static constexpr float MOVEMENT_FORCE = 35775.0f;
	static constexpr float SMALL_BALL_SIZE = 25;
	static constexpr float BIG_SMALL_BALL_RATIO = 3.0f/2.0f;
	static constexpr float BIG_BALL_SIZE = SMALL_BALL_SIZE * BIG_SMALL_BALL_RATIO;

	

	//  FOR GRID OF GAME
	static constexpr float WORLD_SIZE_X = WINDOW_WIDTH;
	static constexpr float WORLD_SIZE_Y = WINDOW_HEIGHT;
	static constexpr float BASE_GRID_SIZE_X = 80.0F ;
	static constexpr float BASE_GRID_SIZE_Y = 60.0F ;// THIS IS OPTIMIZED FOR THE 800X600 SCREEN
	static constexpr float GRID_COUNT_X = WORLD_SIZE_X / BASE_GRID_SIZE_X;
	static constexpr float GRID_COUNT_Y = WORLD_SIZE_Y / BASE_GRID_SIZE_Y;


	// Just make sure UPDATE_DRAW_RANGE is always greater than POTENTIAL_COLLISION_RANGE
	// It wont make any problem but u r just processing extra chunks of object
	// which wont ever gets updated or drawn
	static constexpr unsigned int POTENTIAL_COLLISION_RANGE = 1; // this is a grid range, means it checks n block out of player in all direction
	static constexpr unsigned int UPDATE_DRAW_RANGE = 3; // this is a grid range ,means it checks n block out of player in all direction





};


enum CollisionId {
	PlayerId = 0 ,
	LightPathId = 2 ,
	HeavyPathId = 3 ,
	BouncyPathId = 4,
	InfilatorId = 5,
	DeflatorId = 6
};


class VectorOperation {
public:
	static inline float DotProduct(const sf::Vector2f& vector) { return (vector.x * vector.x) +(vector.y * vector.y); }
	static inline float DotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) { return (v1.x * v2.x) + (v1.y * v2.y); }
	static inline float Magnitude(const sf::Vector2f& vector) {return std::sqrt(DotProduct(vector));}
	static inline float DistanceBetweenTwoVector(const sf::Vector2f& v1, const sf::Vector2f& v2) {
		return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
	}
	static inline sf::Vector2f Normalize(sf::Vector2f& vector) {
		auto M = Magnitude(vector);
		if (M == 0) { M = 1; }   // std::cerr << " division by zero " << std::endl;}
		return { vector.x / M , vector.y / M };
	}
	VectorOperation() = default;
};
