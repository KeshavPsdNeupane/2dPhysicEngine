#pragma once
#include"../State.h"
#include<SFML/Graphics.hpp>
#include"../../StateObjects.h"
#include<array>

class GameOver : public Engine::State {
private:
	std::shared_ptr<StateData> stateData;
	std::string previousLevelFilePath;
	sf::Event event;
	sf::Text gameMenuTitle;
	std::array<sf::Text, 3> texts;
	short IsSetectedIndex;
	short IsPressedIndex;

public:
	GameOver(std::shared_ptr<StateData> stateData , const std::string& previousLevelFilePath);
	~GameOver();

public:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;

};
