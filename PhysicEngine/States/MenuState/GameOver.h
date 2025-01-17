#pragma once
#include"../State.h"
#include<SFML/Graphics.hpp>
#include"../../StateObjects.h"

class GameOver : public Engine::State {
private:
	std::shared_ptr<StateData> stateData;
	sf::Event event;
	float DELTA_TIME;

	sf::Text title;
	sf::Text gameMenuTitle;
	sf::Text rePlayButton;
	sf::Text exitButton;
	bool isRePlayButtonSelected;
	bool isExitButtonSelected;

	bool isRePlayButtonPressed;
	bool isExitButtonPressed;
public:
	GameOver(std::shared_ptr<StateData> stateData);
	~GameOver();

public:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;

};
