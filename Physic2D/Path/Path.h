#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../Body/RigidBody.h"
#include"../Body/ContactMechanic.h"
class Path : public 	RigidBody , public ContactMech {
private:
	std::shared_ptr<sf::RectangleShape> path;

public:
	Path() = default;

	Path(const int id, const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Vector2f& velocity,
		const sf::Vector2f& accleration, const float& mass);
	inline std::shared_ptr<sf::RectangleShape> GetShape() { return path; }
	inline RigidBody& GetFrame() { return *this; }
	inline ContactMech& GetContactHandler() { return *this; }

public:
	void Load();
	void Update(const float& DT);
	void PathBasedCollisionHandle(sf::FloatRect& Bound1, RigidBody& F1,
		sf::FloatRect& Bound2, RigidBody& F2) override;
	void Draw(std::shared_ptr<sf::RenderWindow> window);

private:
	inline void FindMaxVelocities() override;
};

