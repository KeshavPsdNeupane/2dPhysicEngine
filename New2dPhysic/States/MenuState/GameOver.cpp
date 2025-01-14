#include "GameOver.h"
#include"../../Gameplay.h"

GameOver::GameOver(std::shared_ptr<StateData> stateData) :
	stateData(stateData), DELTA_TIME(0.0f),
	isRePlayButtonSelected(true), isRePlayButtonPressed(false),
	isExitButtonSelected(false), isExitButtonPressed(false), event() {
}

GameOver::~GameOver() {}

void GameOver::Load() {
	// main menu game title
	this->gameMenuTitle.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
	this->gameMenuTitle.setString("GAMEOVER");
	this->gameMenuTitle.setCharacterSize(35);
	auto pos = this->stateData->window->getSize();
	auto bound = this->gameMenuTitle.getLocalBounds();
	this->gameMenuTitle.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->gameMenuTitle.setPosition(pos.x / 2.0f, pos.y / 2.0f - 150.f);

	// play button
	this->rePlayButton.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
	this->rePlayButton.setString("REPLAY");
	this->rePlayButton.setCharacterSize(24);
	bound = this->rePlayButton.getLocalBounds();
	this->rePlayButton.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->rePlayButton.setPosition(pos.x / 2.0f, pos.y / 2.0f - 25.0f);

	// exit button
	this->exitButton.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
	this->exitButton.setString("EXIT");
	this->exitButton.setCharacterSize(24);
	bound = this->exitButton.getLocalBounds();
	this->exitButton.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->exitButton.setPosition(pos.x / 2.0f, pos.y / 2.0f + 25.0f);


}

void GameOver::ProcessInput() {
	while (this->stateData->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->stateData->window->close();
		}
		else if (this->event.type == sf::Event::KeyPressed) {
			switch (this->event.key.code) {
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
				if (!this->isRePlayButtonSelected) {
					this->isRePlayButtonSelected = true;
					this->isExitButtonSelected = false;
				}
				break;

			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				if (!this->isExitButtonSelected) {
					this->isExitButtonSelected = true;
					this->isRePlayButtonSelected = false;
				}
				break;



			case sf::Keyboard::Return:
				this->isRePlayButtonPressed = false;
				this->isExitButtonPressed = false;

				if (this->isRePlayButtonSelected) {
					this->isRePlayButtonPressed = true;
					this->isExitButtonPressed = false;
				}
				else {
					this->isExitButtonPressed = true;
					this->isRePlayButtonPressed = false;
				}
				break;

			default:
				break;
			}
		}

	}
}

void GameOver::Update(const float& dt) {
	this->DELTA_TIME = dt;
	if (this->isRePlayButtonSelected) {
		this->rePlayButton.setFillColor(sf::Color::Red);
		this->exitButton.setFillColor(sf::Color::White);
	}
	else {
		this->exitButton.setFillColor(sf::Color::Red);
		this->rePlayButton.setFillColor(sf::Color::White);
	}
	if (isRePlayButtonPressed) {
		this->stateData->stateManager->AddState(std::make_unique<Gameplay>(this->stateData), true);
	}
	else if (isExitButtonPressed) {
		this->stateData->window->close();
	}
	else {
	}
}

void GameOver::Draw() {
	this->stateData->window->clear(sf::Color::Black);


	this->stateData->window->draw(this->gameMenuTitle);
	this->stateData->window->draw(this->rePlayButton);
	this->stateData->window->draw(this->exitButton);


	this->stateData->window->display();
}
