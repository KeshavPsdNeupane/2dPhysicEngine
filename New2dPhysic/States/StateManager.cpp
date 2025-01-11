#include "StateManager.h"

Engine::StateManager::StateManager():
isAdd(false), isReplace(false), isRemove(false){}

Engine::StateManager::~StateManager(){}

void Engine::StateManager::AddState(std::unique_ptr<Engine::State> state, bool isReplacing){
	this->isAdd = true;
	this->newState = std::move(state);
	this->isReplace = isReplacing;
}

void Engine::StateManager::RemoveState(){
	this->isRemove = true;
}

void Engine::StateManager::ProcessStateChanges(){
	if (this->isRemove && !this->states.empty()) {
		this->states.pop();
		if (!this->states.empty()) {
			this->states.top()->Start();
		}
		this->isRemove = false;
	}
	if (this->isAdd) {
		if (!this->states.empty()) {
			if (this->isReplace) {
				this->states.pop();
			}
			else {
				this->states.top()->Pause();
			}
		}
		this->states.push(std::move(this->newState));
		this->states.top()->Load();
		this->isAdd = false;
	}
}

std::unique_ptr<Engine::State>& Engine::StateManager::GetActiveState(){
	return this->states.top();
}
