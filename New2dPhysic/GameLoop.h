#pragma once
#include<SFML/Graphics.hpp>
#include"Resources/States/StateManager.h"
#include"StateObjects.h"

class Gameloop{
private:
	std::shared_ptr<StateData> stateData;
	sf::Clock clock;
	float DELTA_TIME;
public:
	Gameloop();
	~Gameloop();

public:
	void Run();
private:
	void LoadAllAssets();
};

