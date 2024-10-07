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

	// FOR RIGITBODY
	static constexpr float COEFF_MAX_VELOCITY_X = 9000.0f;
	static constexpr float COEFF_MAX_VELOCITY_Y = 1936.5f;
	static constexpr float ABSOLUTE_MAX_VELOCITY_X = 400.0f;
	static constexpr float ABSOLUTE_MAX_VELOCITY_Y = 800.0f;
	static constexpr float COLLISION_VELOCITY_THRESHOLD = 2.5f;
	static constexpr float MASS_THRESHOLD = 1000.0f;



	static constexpr float COEFF_OF_RESTITUTION_OBJECT_X = .2f;
	static constexpr float COEFF_OF_RESTITUTION_PATH_X = .7f;

	static constexpr float COEFF_OF_RESTITUTION_OBJECT_Y = .6f;
	static constexpr float COEFF_OF_RESTITUTION_PATH_Y = .8f;


	
	static constexpr float COEFF_OF_FRICTION_PATH = 0.7f;
	static constexpr float COEFF_OF_FRICTION_OBJECT = 0.0f;

	// RECT
	static constexpr float GRAVITY = 50.0f * 10.0f;
	static constexpr float ABSOLUTE_ACCLERATION_FOR_PLAYER_X = 5000.0f;
	static constexpr float ABSOLUTE_ACCLERATION_FOR_PLAYER_Y = 1000.0f;
	// HERE 50 IS A MODIFIER AND 10 IS ACTUAL VALUE JUST LIKE IRL G OF 9.8 OR 10M/S

	//  FOR GRID OF GAME
	static constexpr float WORLD_SIZE_X = WINDOW_WIDTH;
	static constexpr float WORLD_SIZE_Y = WINDOW_HEIGHT;
	static constexpr float BASE_GRID_SIZE_X = 80.0F ;
	static constexpr float BASE_GRID_SIZE_Y = 60.0F ;// THIS IS OPTIMIZED FOR THE 800X600 SCREEN
	static constexpr float GRID_COUNT_X = WORLD_SIZE_X / BASE_GRID_SIZE_X;
	static constexpr float GRID_COUNT_Y = WORLD_SIZE_Y / BASE_GRID_SIZE_Y;
	// WILL FILL MORE GRID ON SIZE 
};



class VectorOperation {
	float a;
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
};


class BasicKinematic:public VectorOperation {
public:
	static sf::Vector2f Distance(const sf::Vector2f& u, const sf::Vector2f& a, const float& t);
	static sf::Vector2f Distance(const sf::Vector2f& u, const sf::Vector2f& v, const sf::Vector2f& a);
	static float GetTime(const sf::Vector2f& u, const sf::Vector2f& v, const sf::Vector2f& a);
	static float GetTime2(const sf::Vector2f& u, const sf::Vector2f& a , const sf::Vector2f& s);
	static sf::Vector2f FinalVelocity1(const sf::Vector2f& u, const sf::Vector2f& a, const float& t);
	static sf::Vector2f FinalVelocity2(const sf::Vector2f& u, const sf::Vector2f& a, const sf::Vector2f& s);
};