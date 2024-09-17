#pragma once
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
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
		if (M == 0) { std::cerr << " division by zero " << std::endl; }
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