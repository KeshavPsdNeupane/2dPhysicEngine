#pragma once
#include"../States/State.h"
#include"../StateObjects.h"



class WorldSuperClass : public Engine::State{
protected:
	sf::Vector2f worldSize;
	sf::Vector2f tileSize;

	std::shared_ptr<StateData> stateData;
	sf::View worldView;
	unsigned int points;
	unsigned short life;
	unsigned short maxLife;
	sf::Vector2f checkPointPosition;
public:
	WorldSuperClass(std::shared_ptr<StateData> stateData , 
		unsigned short l = 3, unsigned short maxLife = 5 ,unsigned int initpoint = 0 );
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


public:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;
};

