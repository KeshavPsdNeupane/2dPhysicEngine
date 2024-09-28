#pragma once
#include"PhysicLoop.h"
#include"Body/RigidBody.h"
#include"PhysicUtility/Utility.h"
#include"Objects/Rect.h"
#include"Body/ContactMechanic.h"
#include"Path/Path.h"
#include"Resources/Resources.h"
#include"GameGrid/GameGrid.h"
#include<vector>
struct GameObject {
	GameGrid grid;
	Resources resource;
	Rect rectangle{ 1,sf::Vector2f(400, 200), sf::Vector2f(25,25)};
	std::vector<Path>path = { {4,{10.0f,530.0f} , {780.0f,50.0f},{0,0},{0,0} , 40000} , 
		{5,{10.0f,100.0f} , {70.0f,430.0f},{0,0},{0,0} , 400000},
	{6,{720.0f,100.0f} , {70.0f,430.0f},{0,0},{0,0} , 400000} };
	PhysicLoop loop;
};

extern GameObject gameObject;