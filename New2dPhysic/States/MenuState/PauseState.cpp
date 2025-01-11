#include "PauseState.h"
#include"../../Gameplay.h"

PauseState::PauseState(std::shared_ptr<StateData> stateData) :
	stateData(stateData), DELTA_TIME(0.0f),
	isResumeButtonSelected(true), isResumeButtonPressed(false),
	isExitButtonSelected(false), isExitButtonPressed(false), event() {}

PauseState::~PauseState() {}

void PauseState::Load() {
	// main menu game title
	this->gameMenuTitle.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
	this->gameMenuTitle.setString("PHYSIC ENGINE");
	this->gameMenuTitle.setCharacterSize(35);
	auto pos = this->stateData->window->getSize();
	auto bound = this->gameMenuTitle.getLocalBounds();
	this->gameMenuTitle.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->gameMenuTitle.setPosition(pos.x / 2.0f, pos.y / 2.0f - 150.f);

	// play button
	this->resumeButton.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
	this->resumeButton.setString("RESUME");
	this->resumeButton.setCharacterSize(24);
	bound = this->resumeButton.getLocalBounds();
	this->resumeButton.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->resumeButton.setPosition(pos.x / 2.0f, pos.y / 2.0f - 25.0f);

	// exit button
	this->exitButton.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
	this->exitButton.setString("EXIT");
	this->exitButton.setCharacterSize(24);
	bound = this->exitButton.getLocalBounds();
	this->exitButton.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->exitButton.setPosition(pos.x / 2.0f, pos.y / 2.0f + 25.0f);


}

void PauseState::ProcessInput() {
	while (this->stateData->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->stateData->window->close();
		}
		else if (this->event.type == sf::Event::KeyPressed) {
			switch (this->event.key.code) {
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
				if (!this->isResumeButtonSelected) {
					this->isResumeButtonSelected = true;
					this->isExitButtonSelected = false;
				}
				break;

			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				if (!this->isExitButtonSelected) {
					this->isExitButtonSelected = true;
					this->isResumeButtonSelected = false;
				}
				break;



			case sf::Keyboard::Return:
				this->isResumeButtonPressed = false;
				this->isExitButtonPressed = false;

				if (this->isResumeButtonSelected) {
					this->isResumeButtonPressed = true;
					this->isExitButtonPressed = false;
				}
				else {
					this->isExitButtonPressed = true;
					this->isResumeButtonPressed = false;
				}
				break;

			default:
				break;
			}
		}

	}
}

void PauseState::Update(const float& dt) {
	this->DELTA_TIME = dt;
	if (this->isResumeButtonSelected) {
		this->resumeButton.setFillColor(sf::Color::Red);
		this->exitButton.setFillColor(sf::Color::White);
	}
	else {
		this->exitButton.setFillColor(sf::Color::Red);
		this->resumeButton.setFillColor(sf::Color::White);
	}
	if (isResumeButtonPressed) {
		this->stateData->stateManager->RemoveState();
	}
	else if (isExitButtonPressed) {
		this->stateData->window->close();
	}
	else {
	}
}

void PauseState::Draw() {
    this->stateData->window->clear(sf::Color::Black);

	this->stateData->window->draw(this->gameMenuTitle);
	this->stateData->window->draw(this->resumeButton);
	this->stateData->window->draw(this->exitButton);


	this->stateData->window->display();
}
