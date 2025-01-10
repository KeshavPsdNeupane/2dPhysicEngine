#pragma once
#include"../State.h"
#include<SFML/Graphics.hpp>
#include"../../StateObjects.h"
class PauseState : public Engine::State {
private:
	std::shared_ptr<StateData> stateData;
	sf::Event event;
	float DELTA_TIME;

	sf::Text title;
	sf::Text gameMenuTitle;
	sf::Text resumeButton;
	sf::Text exitButton;
	bool isResumeButtonSelected;
	bool isExitButtonSelected;

	bool isResumeButtonPressed;
	bool isExitButtonPressed;
public:
	PauseState(std::shared_ptr<StateData> stateData);
	~PauseState();

public:
	void Load() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Draw() override;

};
