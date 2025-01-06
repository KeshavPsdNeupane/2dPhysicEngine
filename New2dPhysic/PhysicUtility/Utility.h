#pragma once
#include<cmath>
#include<iostream>

namespace GMNumber {
	//  FOR WINDOWS 
	static constexpr float WINDOW_WIDTH = 800.0f;
	static constexpr float WINDOW_HEIGHT = 600.0f;
	static constexpr int MAX_FRAME_RATE = 60; ;
	static constexpr float PI = 3.14159265359f;

	//--------------------------------------------------------------------------------
	static constexpr float GRAVITY = 60.0f * 10.0f;// HERE 50 IS A MODIFIER AND 10 IS ACTUAL VALUE JUST LIKE IRL G OF 9.8 OR 10M/S
	static constexpr float AIR_COEFFICIENT_OF_DRAG = 0.47f;
	static constexpr float AIR_DENSITY = 1.225f;
 

	//for RIGIDBODY
	// The coefficient for the maximum velocity in the x direction.
	// This coefficient acts as a force but can be thought of as a scaling factor.
	// The relation for the velocity is: velocity = force / mass
	// 9000.0f acts as a force but you can think of it as a coefficient.
	// The coefficient maps to a terminal velocity of 200 with a mass of 60.
	// For other masses, the terminal velocity can be calculated as: vt.x = 9000.0f / mass
	static constexpr float COEFF_MAX_VELOCITY_X = 9000.0f;

	// The coefficient for the maximum velocity in the y direction.
	// The relation is: vt =  sqrt(K * 2 * g * m / (p * a * cd))
	// K is the constant COEFF_MAX_VELOCITY_Y = 1672.98f
	// where vt is terminal velocity, g is gravity, m is mass, p is air density, a is area, and cd is the coefficient of drag.
	// The value used are m = 60, area = 24*24, cd = 0.47, p = 1.225, gravity = 500 for this mapping.
	// The relation with the coefficient is: vt = sqrt(2972.41 * (2 * m * g) / (p * cd))
	// The coefficient has a direct proportional relation with sqrt(mass) and sqrt(gravity),
	// and an inverse proportional relation with sqrt(area).
	// The area and mass are obtained from the respective class functions.
	static constexpr float COEFF_MAX_VELOCITY_Y = 1672.98f * (2.0f * GRAVITY) / (AIR_DENSITY * AIR_COEFFICIENT_OF_DRAG);


	// the  two values are the maximum velocity that can be achieved by the object
	// if the object is pushed by a force greater than the force required to achieve this velocity
	// the object will still move with this velocity
	// this is done to prevent the object from moving with infinite velocity
	// the object will move with this velocity in the direction of the force applied
	static constexpr float ABSOLUTE_MAX_VELOCITY_X = 400.0f;
	static constexpr float ABSOLUTE_MAX_VELOCITY_Y = 800.0f;


	// the above two are the threshold for the object to be considered as stationary
	// if the object has a velocity less than the LOWEST_VELOCITY_THRESHOLD
	// and mass greater than MASS_THRESHOLD
	// the object will be considered as stationary
	// this is done to prevent the object from moving with very low velocity
	static constexpr float LOWEST_VELOCITY_THRESHOLD = 0.4f;
	static constexpr float MASS_THRESHOLD = 1000.0f;



	//FOR COEFF OF RESTITUTION
		// values are the coefficient of restitution for the object and path
	// the coefficient of restitution is the ratio of the final velocity to the initial velocity
	static constexpr float COEFF_OF_RESTITUTION_OBJECT_X = 0.2f;
	static constexpr float COEFF_OF_RESTITUTION_OBJECT_Y = 0.3f;
	static constexpr float COEFF_OF_RESTITUTION_PATH_X = 0.7f;
	static constexpr float COEFF_OF_RESTITUTION_PATH_Y = 0.4f;


	//COLLISION THRESHOLD CALCULATION


		// the above two are the threshold for the object to be considered after colliding
	// if the object has a velocity less than the COLLISION_VELOCITY_THRESHOLD_X
	// and COLLISION_VELOCITY_THRESHOLD_Y it will mapp the respective velocity to 0.0f
	static constexpr float COLLISION_VELOCITY_THRESHOLD_X = GRAVITY * (1.0f/ MAX_FRAME_RATE)
		* (COEFF_OF_RESTITUTION_OBJECT_X + COEFF_OF_RESTITUTION_PATH_X)/4.0f;
	static constexpr float COLLISION_VELOCITY_THRESHOLD_Y = GRAVITY * (1.0f / MAX_FRAME_RATE)
		* (COEFF_OF_RESTITUTION_OBJECT_Y + COEFF_OF_RESTITUTION_PATH_Y ) / 2.0f;


	// FOR COEFFICIENT OF FRICTION
	static constexpr float COEFF_OF_FRICTION_PATH = 0.5f;
	static constexpr float COEFF_OF_FRICTION_OBJECT = 0.0f;
	// the above two are the coefficient of friction for the object and path

	// RECT

	static constexpr float ABSOLUTE_ACCLERATION_FOR_PLAYER_X = 4000.0f;
	static constexpr float ABSOLUTE_ACCLERATION_FOR_PLAYER_Y = 800.0f;
	static constexpr float MOVEMENT_FORCE = 35775.0f;
	static constexpr float SMALL_BALL_SIZE = 24;
	static constexpr float BIG_SMALL_BALL_RATIO = 3.0f/2.0f;
	static constexpr float BIG_BALL_SIZE = SMALL_BALL_SIZE * BIG_SMALL_BALL_RATIO;
	static constexpr float READJUST_SIZE = SMALL_BALL_SIZE * (BIG_SMALL_BALL_RATIO -1.0f);
	static constexpr float ELASTICITY_RATIO = 1.25f;
	// the above are the constants for the player object
	// ABSOLUTE_ACCLERATION_FOR_PLAYER_X is the maximum acceleration in the x direction
	// ABSOLUTE_ACCLERATION_FOR_PLAYER_Y is the maximum acceleration in the y direction
	// MOVEMENT_FORCE is the force applied to the player object
	

	//  FOR GRID OF GAME
	static constexpr float WORLD_SIZE_X = WINDOW_WIDTH;
	static constexpr float WORLD_SIZE_Y = WINDOW_HEIGHT;
	static constexpr float BASE_GRID_SIZE_X = 80.0F ;
	static constexpr float BASE_GRID_SIZE_Y = 60.0F ;// THIS IS OPTIMIZED FOR THE 800X600 SCREEN
	static constexpr float GRID_COUNT_X = WORLD_SIZE_X / BASE_GRID_SIZE_X;
	static constexpr float GRID_COUNT_Y = WORLD_SIZE_Y / BASE_GRID_SIZE_Y;
	// the above are the constants for the grid of the game
	// WORLD_SIZE_X is the width of the game world
	// WORLD_SIZE_Y is the height of the game world
	// BASE_GRID_SIZE_X is the width of the grid cell
	// BASE_GRID_SIZE_Y is the height of the grid cell
	// GRID_COUNT_X is the number of grid cells in the x direction
	//	GRID_COUNT_Y is the number of grid cells in the y direction
	// the grid is used to optimize the collision detection and drawing of the objects


	// Just make sure UPDATE_DRAW_RANGE is always greater than POTENTIAL_COLLISION_RANGE
	// It wont make any problem but u r just processing extra chunks of object
	// which wont ever gets updated or drawn
	static constexpr unsigned int POTENTIAL_COLLISION_RANGE = 1; // this is a grid range, means it checks n block out of player in all direction
	static constexpr unsigned int UPDATE_DRAW_RANGE = 3; // this is a grid range ,means it checks n block out of player in all direction
	// the above two are the constants for the grid of the game
	// POTENTIAL_COLLISION_RANGE is the range of the grid cells to check for potential collision
	// UPDATE_DRAW_RANGE is the range of the grid cells to update and draw the objects
	// the grid is used to optimize the collision detection and drawing of the objects




};


enum CollisionId {
	PlayerId = 0 ,
	LightPathId = 2 ,
	HeavyPathId = 3 ,
	BouncyPathId = 4,
	InflatorId = 5,
	DeflatorId = 6,
	CollectableId = 7
};


class VectorOperation {
public:
	static inline float DotProduct(const sf::Vector2f& vector) { return (vector.x * vector.x) +(vector.y * vector.y); }
	static inline float DotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) { return (v1.x * v2.x) + (v1.y * v2.y); }
	static inline float Magnitude(const sf::Vector2f& vector) {return std::sqrt(DotProduct(vector));}
	static inline float DistanceBetweenTwoVector(const sf::Vector2f& v1, const sf::Vector2f& v2) {
		return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
	}
	static inline sf::Vector2f Normalize(sf::Vector2f vector) {
		auto M = std::sqrt(vector.x * vector.x + vector.y * vector.y);
		if (M == 0) { M = 1; }   // to avoid division by zero
		return { vector.x / M , vector.y / M };
	}
	VectorOperation() = default;
};
