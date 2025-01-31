#pragma once
#include<cmath>
#include<SFML/Graphics.hpp>

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
	static constexpr float COEFF_MAX_VELOCITY_X = 16000.0f;

	// The coefficient for the maximum velocity in the y direction.
	// The relation is: vt =  sqrt(K * 2 * g * m / (p * a * cd))
	// K is the constant COEFF_MAX_VELOCITY_Y = 1672.98f
	// where vt is terminal velocity, g is gravity, m is mass, p is air density, a is area, and cd is the coefficient of drag.
	// The value used are m = 60, area = 24*24, cd = 0.47, p = 1.225, gravity = 500 for this mapping.
	// The relation with the coefficient is: vt = sqrt(2972.41 * (2 * m * g) / (p * cd))
	// The coefficient has a direct proportional relation with sqrt(mass) and sqrt(gravity),
	// and an inverse proportional relation with sqrt(area).
	// The area and mass are obtained from the respective class functions.
	static constexpr float COEFF_MAX_VELOCITY_Y = 2972.41f * (2.0f * GRAVITY) / (AIR_DENSITY * AIR_COEFFICIENT_OF_DRAG);


	// the  two values are the maximum velocity that can be achieved by the object
	// if the object is pushed by a force greater than the force required to achieve this velocity
	// the object will still move with this velocity
	// this is done to prevent the object from moving with infinite velocity
	// the object will move with this velocity in the direction of the force applied
	static const sf::Vector2f ASOLUTE_MAX_VELOCITY = { 500.0f, 800.0f };




	// these two are the threshold for the object to be considered as stationary
	// if the object has a velocity less than the LOWEST_VELOCITY_THRESHOLD
	// and mass greater than MASS_THRESHOLD
	// the object will be considered as stationary
	// this is done to prevent the object from moving with very low velocity
	static constexpr float LOWEST_VELOCITY_THRESHOLD = 0.4f;
	static constexpr float MASS_THRESHOLD = 1000.0f;



	//FOR COEFF OF RESTITUTION
	// values are the coefficient of restitution for the object and path
	// the coefficient of restitution is the ratio of the final velocity to the initial velocity

	static const sf::Vector2f COEFF_OF_RESTITUTION_OBJECT(0.2f, 0.3f) ;
	static const sf::Vector2f COEFF_OF_RESTITUTION_PATH(0.7f, 0.4f) ;

	//COLLISION THRESHOLD CALCULATION
	// the two are the threshold for the object to be considered after colliding
	// if the object has a velocity less than the COLLISION_VELOCITY_THRESHOLD_X
	// and COLLISION_VELOCITY_THRESHOLD_Y it will mapp the respective velocity to 0.0f
	static constexpr float NEGATE_DISTANCE_FROM_COLLISION = 0.11f * GRAVITY / 500.0f;
	static const sf::Vector2f COlliSION_VELOCITY_THRESHOLD(GRAVITY* (1.0f / MAX_FRAME_RATE)
		* (COEFF_OF_RESTITUTION_OBJECT.x + COEFF_OF_RESTITUTION_PATH.x) * 0.5f,
		GRAVITY* (1.0f / MAX_FRAME_RATE)
		* (COEFF_OF_RESTITUTION_OBJECT.y + COEFF_OF_RESTITUTION_PATH.y)*
		std::pow(1.5f,NEGATE_DISTANCE_FROM_COLLISION));


	// FOR COEFFICIENT OF FRICTION
	static constexpr float COEFF_OF_FRICTION_PATH = 0.7f;
	static constexpr float COEFF_OF_FRICTION_OBJECT = 0.0f;
	// the above two are the coefficient of friction for the object and path

	// RECT
	static constexpr bool IS_PADDING = false;
	static const sf::Vector2f ABSOLUTE_ACCLERATION_FOR_PLAYER = { 4000.0f, 800.0f };
	static constexpr float SMALL_BALL_SIZE = 32;
	static constexpr float HARDCOADED_SMALL_BALL_SIZE = 25;
	static constexpr float BIG_SMALL_BALL_RATIO = 1.5f;
	static constexpr float BIG_BALL_SIZE = SMALL_BALL_SIZE * BIG_SMALL_BALL_RATIO;
	static constexpr float READJUST_SIZE = SMALL_BALL_SIZE * (BIG_SMALL_BALL_RATIO - 1.0f);
	static constexpr float BALL_BOUNCE_DISTANCE =  64.0f * 3.0f; // 64 is size of grid 2.0f is multiplier  
	static constexpr float ELASTICITY_RATIO = 1.19f;  
	// 1.19 is the ratio of the jump force of big ball to small ball
	

	// Just make sure UPDATE_DRAW_RANGE is always greater than POTENTIAL_COLLISION_RANGE
	// It wont make any problem but u r just processing extra chunks of object
	// which wont ever gets updated or drawn
	static constexpr unsigned int POTENTIAL_COLLISION_RANGE = 1; // this is a grid range, means it checks n block out of player in all direction
	static constexpr unsigned int UPDATE_DRAW_RANGE = 6; // this is a grid range ,means it checks n block out of player in all direction
	// the above two are the constants for the grid of the game
	// POTENTIAL_COLLISION_RANGE is the range of the grid cells to check for potential collision
	// UPDATE_DRAW_RANGE is the range of the grid cells to update and draw the objects
	// the grid is used to optimize the collision detection and drawing of the objects

	const static sf::Vector2i SEARCH_RANGE_FOR_UPDATE_DRAW = {7,5};


	// FOR TEXTURE OF ALL OBJECTS EXCEPT PLAYER
	static constexpr int TEXTURE_COUNT_X = 12;
	static constexpr int TEXTURE_SIZE = 64;
	static constexpr int PLAYER_SPRITE_SIZE = 25;

};


namespace MyColor {
	static sf::Color purple = sf::Color(128, 0, 128);    // Purple
	static sf::Color orange = sf::Color(255, 165, 0);    // Orange
	static sf::Color teal = sf::Color(0, 128, 128);    // Teal
	static sf::Color chocolate = sf::Color(210, 105, 30);   // Chocolate
	static sf::Color indigo = sf::Color(75, 0, 130);     // Indigo
	static sf::Color lightBlue = sf::Color(173, 216, 230);  // Light Blue
	static sf::Color forestGreen = sf::Color(34, 139, 34);    // Forest Green
	static sf::Color deepPink = sf::Color(255, 20, 147);   // Deep Pink
	static sf::Color darkSlateGray = sf::Color(47, 79, 79);     // Dark Slate Gray
	static sf::Color gold = sf::Color(255, 215, 0);    // Gold
};


enum CollisionId {
	PlayerId = 0 ,
	LightPathId = 2 ,
	HeavyPathId = 3 ,
	BouncyPathId = 4,
	InflatorId = 5,
	DeflatorId = 6,
	CollectableId = 7,
	StaticEnemyId  = 8,
	CheckPointId = 9,
	StaticEnemyIdS = 10,
	InvisibleEnemyId = 11,
	EndGameMarkerId = 12,
};



class VectorOperation {
public:
	VectorOperation() = default;
public:
	static inline float DotProduct(const sf::Vector2f& vector)
	{ return (vector.x * vector.x) +(vector.y * vector.y); }

	static inline float DotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2)
	{ return (v1.x * v2.x) + (v1.y * v2.y); }

	static inline float Magnitude(const sf::Vector2f& vector) 
	{return std::sqrt(vector.x * vector.x + vector.y * vector.y);}

	static inline float DistanceBetweenTwoVector(const sf::Vector2f& v1, const sf::Vector2f& v2) {
		return std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
	}
	static inline sf::Vector2f Normalize(sf::Vector2f vector) {
		auto M = std::sqrt(vector.x * vector.x + vector.y * vector.y);
		if (M == 0) { M = 1; }   // to avoid division by zero
		return { vector.x / M , vector.y / M };
	}

	static void ClampForVector(sf::Vector2f& current, const sf::Vector2f& min, const sf::Vector2f& max) {
		if (current.x < min.x) { current.x = min.x; }
		if (current.y < min.y) { current.y = min.y; }
		if (current.x > max.x) { current.x = max.x; }
		if (current.y > max.y) { current.y = max.y; }
		return;
	}

	template<typename T>
	static T Clamp(T current, const T min, const T max) {
		if (current < min) { current = min; }
		if (current > max) { current = max; }
		return current;
	}
};

