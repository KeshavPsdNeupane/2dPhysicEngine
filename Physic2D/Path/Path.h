#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../Body/RigidBody.h"

class Path : public 	RigidBody {
private:
	int id;
	sf::RectangleShape path;

public:
	Path() = default;
	Path(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Vector2f& velocity,
		const sf::Vector2f& accleration, const float& mass);
	inline sf::RectangleShape& GetShape() { return path; }
	inline RigidBody& GetFrame() { return *this; }

public:
	void Load();
	void Update(const float& DT);
	void Draw(std::shared_ptr<sf::RenderWindow> window);
};

