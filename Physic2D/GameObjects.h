#pragma once
#include"PhysicLoop.h"
#include"Body/RigidBody.h"
#include"PhysicUtility/Utility.h"
#include"Objects/Rect.h"
#include"Body/Collision.h"
#include"Path/Path.h"
struct GameObject {
	Rect rectangle{ sf::Vector2f(400, 200), sf::Vector2f(25,50)};
	Path path{sf::Vector2f(0,500) , sf::Vector2f(800,600)};
	Collision collision;
	PhysicLoop loop;
};

extern GameObject gameObject;