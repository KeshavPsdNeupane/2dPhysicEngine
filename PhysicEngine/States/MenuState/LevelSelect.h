#pragma once
#include"../State.h"
#include<SFML/Graphics.hpp>
#include"../../StateObjects.h"
#include<array>

class LevelSelect : public Engine::State {
private:
	std::shared_ptr<StateData> stateData;
	sf::Event event;
	sf::Text gameMenuTitle;
	std::array<sf::Text, 4> texts;
	short IsSetectedIndex;
	short IsPressedIndex;

public:
	LevelSelect(std::shared_ptr<StateData> stateData);
	~LevelSelect();

public:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;

};
