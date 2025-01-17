#pragma once
#include<SFML/Graphics.hpp>
#include<memory>
#include<iostream>
#include<string>

#include"../Body/ContactMechanic.h"
#include"../GameGrid/GameGrid.h"
#include"../StateObjects.h"
#include"../Player/Rect.h"
#include"../Objects/Inflator.h"
#include"../Objects/Deflator.h"
#include"../Path/BouncyPath.h"
#include"../Objects/Collectable.h"
#include"../Path/Path.h"
#include"../Enemies/StaticEnemy.h"
#include"../Objects/CheckPoint.h"
#include"../World/WorldSuperClass.h"
#include"../GameGrid/OutlineRect.h"
#include"../TileGrid/Tile.h"

class Level1 : public WorldSuperClass{
private:
	bool isPaused;
	sf::Event event;
	GameGrid grid;

	std::shared_ptr<Rect> rectangle;
	std::vector<std::shared_ptr<Path>> path;
	std::shared_ptr<Inflator> inflator;
	std::shared_ptr<Deflator> deflator;
	std::shared_ptr<BouncyPath> bouncyPath;
	std::vector<std::shared_ptr<Collectable>> collectable;

	std::shared_ptr<StaticEnemy> staticEnemy;
	std::shared_ptr<CheckPoint> checkPoint;


	ContactMech contactMechanic;
	GridResult updateDrawResultFromGrid;
	GridResult collisionResultFromGrid;
	sf::Text text;
	sf::Text text2;
	float DT;
	int entityIdCounter;

public:
	Level1(std::shared_ptr<StateData> state);
	~Level1();

private:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;
	void CreateViewBasedOnPlayer(std::shared_ptr<sf::RenderWindow>window);
	void DrawDefaulView(std::shared_ptr<sf::RenderWindow>window);
	void Pause() override;	
	void Start() override;



	void DisplayStats();

private:
	void DeleteUnwanted();


};

