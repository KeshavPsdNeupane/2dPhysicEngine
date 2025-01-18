#include "WorldSuperClass.h"

WorldSuperClass::WorldSuperClass(std::shared_ptr<StateData> stateData, 
	unsigned short l, unsigned short maxlife, unsigned int initpoint):
	stateData(stateData) , life(l),points(initpoint) , maxLife(maxlife) ,
	worldSize() , tileSize(){}

WorldSuperClass::~WorldSuperClass(){}

void WorldSuperClass::Load(){}

void WorldSuperClass::ProcessInput(){}

void WorldSuperClass::Update(const float& dt){}

void WorldSuperClass::Draw(){}
