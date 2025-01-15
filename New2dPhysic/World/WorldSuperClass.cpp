#include "WorldSuperClass.h"

WorldSuperClass::WorldSuperClass(std::shared_ptr<StateData> stateData, 
	unsigned short l, unsigned int initpoint):
	stateData(stateData) , life(l),points(initpoint) {}

WorldSuperClass::~WorldSuperClass(){}

void WorldSuperClass::Load(){}

void WorldSuperClass::ProcessInput(){}

void WorldSuperClass::Update(const float& dt){}

void WorldSuperClass::Draw(){}
