#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../Body/RigidBody.h"

class Path{
private:
	int id;
	sf::RectangleShape path;
	RigidBody frame;
public:
	Path() = default;
	Path(const sf::Vector2f& pos, const sf::Vector2f& size);
	inline sf::RectangleShape& GetShape() { return path; }
	inline RigidBody& GetFrame() { return frame; }
	
public:
	void Load();
	void Update();
	void Draw(std::shared_ptr<sf::RenderWindow> window);
};

