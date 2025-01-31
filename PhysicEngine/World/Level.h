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
#include"../TileGrid/TileResource.h"
#include"../Enemies/InvisibleEnemy.h"
#include"../Enemies/StaticEnemyS.h"
#include"../Enemies/DynamicEnemy.h"

class Level : public WorldSuperClass{
private:
	bool isPaused;
	ContactMech contactMechanic;
	sf::Event event;
	GameGrid grid;
	std::shared_ptr<Rect> rectangle;
	std::vector<std::shared_ptr<Path>> path;
	std::vector<std::shared_ptr<Inflator>> inflator;
	std::vector<std::shared_ptr<Deflator>> deflator;
	std::vector<std::shared_ptr<BouncyPath>> bouncyPath;
	std::vector<std::shared_ptr<Collectable>> collectable;
	std::vector<std::shared_ptr<StaticEnemy>> staticEnemy;
	std::vector<std::shared_ptr<CheckPoint>> checkPoint;
	std::vector<std::shared_ptr<StaticEnemyS>> staticEnemyS;
	std::vector<std::shared_ptr<DynamicEnemy>> dynamicEnemy;
	std::vector<std::shared_ptr<InvisibleEnemy>> invisibleEnemy;

	GridResult updateDrawResultFromGrid;
	GridResult collisionResultFromGrid;
	sf::Text text;
	float DT;
	int entityIdCounter;
public:

	Level(std::shared_ptr<StateData> state,const std::string& filePath);
	~Level();

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
	void CreatePath( const TotalTileData& data , const float& mass,
		const sf::Vector2f& cowffOfRest ,const float& coeffOfFriection);
	void CreateInflator(const TotalTileData& data, const float& mass,
		const sf::Vector2f& cowffOfRest, const float& coeffOfFriection);
	void CreateDeflator(const TotalTileData& data, const float& mass,
		const sf::Vector2f& cowffOfRest, const float& coeffOfFriection);
	void CreateBouncyPath(const TotalTileData& data, const float& mass,
		const sf::Vector2f& cowffOfRest, const float& coeffOfFriection);
	void CreateCollectable(const TotalTileData& data);
	void CreateStaticEnemy(const TotalTileData& data, const float& mass,
		const sf::Vector2f& cowffOfRest, const float& coeffOfFriection);
	void CreateStaticSEnemy(const TotalTileData& data, const float& mass,
		const sf::Vector2f& cowffOfRest, const float& coeffOfFriection);
	void CreateDynamicEnemy(const TotalTileData& data);
	void CreateInvisibleEnemy(const TotalTileData& data);
	void CreateCheckPoint(const TotalTileData& data);
	void CreateEndGameMarker(const TotalTileData& data);
	void EndLevel();

};

