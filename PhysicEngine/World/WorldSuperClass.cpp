#include "WorldSuperClass.h"
#include"../States/MenuState/GameOver.h"



WorldSuperClass::WorldSuperClass(std::shared_ptr<StateData> stateData
	, const std::string filePath,
	unsigned short l, unsigned short maxlife, unsigned int initpoint):
	stateData(stateData) , pathLocation(filePath), life(l), points(initpoint), maxLife(maxlife),
	worldSize() , tileSize(), isLevelEnd(false) , totalCoinCount(0,0){}

WorldSuperClass::~WorldSuperClass(){}

void WorldSuperClass::DecrementCoinCount(){
	if (this->totalCoinCount.x > 0) {
		--this->totalCoinCount.x;
	}
	if (this->totalCoinCount.y > 0) {
		--this->totalCoinCount.y;
	}
	if (this->totalCoinCount.y == 0) {
		this->isLevelEnd = true;
	}
}

void WorldSuperClass::Load(){}

void WorldSuperClass::ProcessInput(){}

void WorldSuperClass::Update(const float& dt){}

void WorldSuperClass::Draw(){}

void WorldSuperClass::PushGameOverState(){
	this->stateData->stateManager->AddState(std::make_unique<GameOver>(this->stateData , this->pathLocation));
}
