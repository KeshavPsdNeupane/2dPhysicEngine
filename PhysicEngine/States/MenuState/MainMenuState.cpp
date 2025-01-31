#include "MainMenuState.h"
#include"../../World/Level.h"
#include"LevelSelect.h"

MainMenu::MainMenu(std::shared_ptr<StateData> stateData):
	stateData(stateData),event(),
IsSetectedIndex(0), IsPressedIndex(-1){}

MainMenu::~MainMenu(){}

void MainMenu::Load(){
	// main menu game title
	const sf::Font& font = this->stateData->resourceManager->GetFont(ResourceId::MAIN_FONT);
	auto pos = this->stateData->window->getSize();
	sf::Vector2f half(pos.x * 0.5f, pos.y * 0.5f);
	sf::FloatRect bound;

	this->gameMenuTitle.setFont(font);
	this->gameMenuTitle.setString("BOUNCE");
	this->gameMenuTitle.setCharacterSize(35);
	bound = this->gameMenuTitle.getLocalBounds();
	this->gameMenuTitle.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->gameMenuTitle.setPosition(half.x , half.x * 0.5f);

	// play button
	this->playButton.setFont(font);
	this->playButton.setString("PLAY");
	this->playButton.setCharacterSize(24);
	bound = this->playButton.getLocalBounds();
	this->playButton.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->playButton.setPosition(half.x, half.y - 25.0f);

	// exit button
	this->exitButton.setFont(font);
	this->exitButton.setString("EXIT");
	this->exitButton.setCharacterSize(24);
	bound = this->exitButton.getLocalBounds();
	this->exitButton.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
	this->exitButton.setPosition(half.x, half.y + 25.0f);


}

void MainMenu::ProcessInput() {
	while (this->stateData->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->stateData->window->close();
		}
		else if (this->event.type == sf::Event::KeyPressed) {
			switch (this->event.key.code) {
			case sf::Keyboard::Up:
			case sf::Keyboard::W:
				this->IsSetectedIndex = VectorOperation::Clamp(this->IsSetectedIndex - 1, 0, 1);
				break;

			case sf::Keyboard::Down:
			case sf::Keyboard::S:
				this->IsSetectedIndex = VectorOperation::Clamp(this->IsSetectedIndex + 1, 0, 1);
				break;

			case sf::Keyboard::Return:
				this->IsPressedIndex = this->IsSetectedIndex;
				break;

			default:
				break;
			}
		}

	}
}

void MainMenu::Update(const float& dt){
	if (this->IsSetectedIndex == 0) {
		this->playButton.setFillColor(sf::Color::Red);
		this->exitButton.setFillColor(sf::Color::White);
	}
	else if (this->IsSetectedIndex == 1) {
		this->exitButton.setFillColor(sf::Color::Red);
		this->playButton.setFillColor(sf::Color::White);
	}

	if (this->IsPressedIndex > -1) {
		if (this->IsPressedIndex == 0) {
			this->stateData->stateManager->AddState(std::make_unique<LevelSelect>(this->stateData), true);
		}
		else if (this->IsPressedIndex == 1) {
			this->stateData->window->close();
		}
	}
}

void MainMenu::Draw(){
	this->stateData->window->clear(sf::Color::Black);
	this->stateData->window->draw(this->gameMenuTitle);
	this->stateData->window->draw(this->playButton);
	this->stateData->window->draw(this->exitButton);
	this->stateData->window->display();
}
