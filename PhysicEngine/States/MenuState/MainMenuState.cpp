#include "MainMenuState.h"
#include"../../World/Level.h"

MainMenu::MainMenu(std::shared_ptr<StateData> stateData):
	stateData(stateData), DELTA_TIME(0.0f),
isPlayButtonSelected(true), isPlayButtonPressed(false),
isExitButtonSelected(false) , isExitButtonPressed(false) ,event(){}

MainMenu::~MainMenu(){}

void MainMenu::Load(){
	// main menu game title
	this->gameMenuTitle.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
	this->gameMenuTitle.setString("BOUNCE");
	this->gameMenuTitle.setCharacterSize(35);
	auto pos = this->stateData->window->getSize();
	auto bound = this->gameMenuTitle.getLocalBounds();
	this->gameMenuTitle.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->gameMenuTitle.setPosition(pos.x / 2.0f, pos.y / 2.0f - 150.f);

	// play button
	this->playButton.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
	this->playButton.setString("PLAY");
	this->playButton.setCharacterSize(24);
	bound = this->playButton.getLocalBounds();
	this->playButton.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->playButton.setPosition(pos.x / 2.0f, pos.y / 2.0f - 25.0f);

	// exit button
	this->exitButton.setFont(this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT));
	this->exitButton.setString("EXIT");
	this->exitButton.setCharacterSize(24);
	bound = this->exitButton.getLocalBounds();
	this->exitButton.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->exitButton.setPosition(pos.x / 2.0f, pos.y / 2.0f + 25.0f);


}

void MainMenu::ProcessInput(){
	while (this->stateData->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->stateData->window->close();
		}
		else if (this->event.type == sf::Event::KeyPressed) {
			switch (this->event.key.code) {
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
				if (!this->isPlayButtonSelected) {
					this->isPlayButtonSelected = true;
					this->isExitButtonSelected = false;
				}
				break;

			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				if (!this->isExitButtonSelected) {
					this->isExitButtonSelected = true;
					this->isPlayButtonSelected = false;
				}
				break;



			case sf::Keyboard::Return:
				this->isPlayButtonPressed = false;
				this->isExitButtonPressed = false;

				if (this->isPlayButtonSelected) {
					this->isPlayButtonPressed = true;
					this->isExitButtonPressed = false;
				}
				else {
					this->isExitButtonPressed = true;
					this->isPlayButtonPressed = false;
				}
				break;

			default:
				break;
			}
		}

	}
}

void MainMenu::Update(const float& dt){
    this->DELTA_TIME = dt;
	if (this->isPlayButtonSelected) {
		this->playButton.setFillColor(sf::Color::Red);
		this->exitButton.setFillColor(sf::Color::White);
	}
	else {
		this->exitButton.setFillColor(sf::Color::Red);
		this->playButton.setFillColor(sf::Color::White);
	}
	if (isPlayButtonPressed) {
		this->stateData->stateManager->AddState(std::make_unique<Level>(this->stateData), true);
	}
	else if (isExitButtonPressed) {
		this->stateData->window->close();
	}
	else {
	}
}

void MainMenu::Draw(){
	this->stateData->window->clear(sf::Color::Black);


	this->stateData->window->draw(this->gameMenuTitle);
	this->stateData->window->draw(this->playButton);
	this->stateData->window->draw(this->exitButton);


	this->stateData->window->display();
}
