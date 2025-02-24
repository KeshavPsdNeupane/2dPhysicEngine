#pragma once
#include"../State.h"
#include<SFML/Graphics.hpp>
#include"../../StateObjects.h"

class MainMenu: public Engine::State{
private:
	std::shared_ptr<StateData> stateData;
	sf::Event event;
	sf::Text gameMenuTitle;
	sf::Text playButton;
	sf::Text exitButton;

	short IsSetectedIndex;
	short IsPressedIndex;

public:
	MainMenu(std::shared_ptr<StateData> stateData);
	~MainMenu();

public:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;

};
