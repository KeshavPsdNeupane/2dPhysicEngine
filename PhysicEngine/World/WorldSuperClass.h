#pragma once
#include"../States/State.h"
#include"../StateObjects.h"
#include"../Objects/LevelEndMarker.h"
#include<string>

class WorldSuperClass : public Engine::State{
protected:
	std::shared_ptr<StateData> stateData;
	std::string pathLocation;
	sf::Vector2f worldSize;
	sf::Vector2f tileSize;
	sf::View worldView;
	sf::Vector2f checkPointPosition;
	unsigned int points;
	unsigned short life;
	unsigned short maxLife;
	bool isLevelEnd;
	sf::Vector2u totalCoinCount;

	std::shared_ptr<LevelEndMarker> levelEndMarker;
public:
	WorldSuperClass(std::shared_ptr<StateData> stateData , const std::string filePath,
		unsigned short l = 2, unsigned short maxLife = 3 ,unsigned int initpoint = 0 );
	~WorldSuperClass();

public:
	void SetPoints(const unsigned int& points) { this->points = points; }	
	const unsigned int& GetPoints() const { return this->points; }
	void SetLife(const unsigned short& live) { this->life = live; }
	const unsigned short& GetLife() const { return this->life; }
	void IncrementLife() { if(this->life < this->maxLife) ++this->life; }
	void DecrementLife() { --this->life; }
	void SetCheckPointPosition(const sf::Vector2f& position) { this->checkPointPosition = position; }
	const sf::Vector2f& GetCheckPointPosition() const { return this->checkPointPosition; }
	void DecrementCoinCount();
	const sf::Vector2u& GetTotalCoinCount() const { return this->totalCoinCount; }
	const bool& GetIsLevelEnd() const { return this->isLevelEnd; }
public:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;


public:
	void PushGameOverState();
};

