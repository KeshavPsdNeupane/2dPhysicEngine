#pragma once
#include<SFML/Graphics.hpp>
#include<memory>
#include<iostream>
#include"Body/ContactMechanic.h"
#include"GameGrid/GameGrid.h"
#include"string"
#include"StateObjects.h"

#include"Objects/Rect.h"
#include"Objects/Inflator.h"
#include"Objects/Deflator.h"
#include"Path/BouncyPath.h"
#include"Objects/Collectable.h"
#include"Path/Path.h"

class Gameplay : public Engine::State{
private:
	bool isPaused;
	std::shared_ptr<StateData> stateData;
	sf::Event event;
	GameGrid grid;

	std::shared_ptr<Rect> rectangle;
	std::vector<std::shared_ptr<Path>> path;
	std::shared_ptr<Inflator> inflator;
	std::shared_ptr<Deflator> deflator;
	std::shared_ptr<BouncyPath> bouncyPath;
	std::vector<std::shared_ptr<Collectable>> collectable;


	GridResult updateDrawResultFromGrid;
	GridResult collisionResultFromGrid;
	sf::Text text;
	sf::Text text2;
	float DT;
	int entityIdCounter;

public:
	Gameplay(std::shared_ptr<StateData> state);
	~Gameplay();

private:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;
	void Pause() override;	
	void Start() override;



	void DisplayStats();

private:
	void DeleteUnwanted();


};

