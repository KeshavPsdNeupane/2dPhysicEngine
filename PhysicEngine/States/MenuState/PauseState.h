#pragma once
#include"../State.h"
#include<SFML/Graphics.hpp>
#include"../../StateObjects.h"
#include<array>

class PauseState : public Engine::State {
private:
	std::shared_ptr<StateData> stateData;
	sf::Event event;
	sf::Text gameMenuTitle;
	std::array<sf::Text, 3> texts;
	short IsSetectedIndex;
	short IsPressedIndex;
	bool isEscPressed;	
public:
	PauseState(std::shared_ptr<StateData> stateData);
	~PauseState();

public:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;

};
