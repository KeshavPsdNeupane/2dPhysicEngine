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
public:
    GameGrid grid;
    Resources resource;
    std::shared_ptr<Rect> rectangle = std::make_shared<Rect>(1, sf::Vector2f(400, 200), sf::Vector2f(25, 25));
    std::vector<std::shared_ptr<Path>> path = {
     std::make_shared<Path>(4, 40000, sf::Vector2f(10.0f, 530.0f), sf::Vector2f(780.0f, 50.0f), sf::Vector2f(0, 0), sf::Vector2f(0, 0)),
     std::make_shared<Path>(5, 400000, sf::Vector2f(10.0f, 100.0f), sf::Vector2f(70.0f, 430.0f), sf::Vector2f(0, 0), sf::Vector2f(0, 0)),
     std::make_shared<Path>(6, 400000, sf::Vector2f(720.0f, 100.0f), sf::Vector2f(70.0f, 430.0f), sf::Vector2f(0, 0), sf::Vector2f(0, 0))
    };

    PhysicLoop loop;
};

extern GameObject gameObject;
