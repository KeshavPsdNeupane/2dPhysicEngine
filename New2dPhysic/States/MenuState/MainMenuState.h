#pragma once
#include"../State.h"
#include<SFML/Graphics.hpp>
#include"../../StateObjects.h"

class MainMenu: public Engine::State{
private:
	std::shared_ptr<StateData> stateData;
	sf::Event event;
	float DELTA_TIME;

	sf::Text title;
	sf::Text gameMenuTitle;
	sf::Text playButton;
	sf::Text exitButton;
	bool isPlayButtonSelected;
	bool isExitButtonSelected;

	bool isPlayButtonPressed;
	bool isExitButtonPressed;
public:
	MainMenu(std::shared_ptr<StateData> stateData);
	~MainMenu();

public:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;

};
